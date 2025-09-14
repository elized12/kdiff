#include "kdiff/Parser.hpp"

namespace kdiff {

Config Parser::parseArgs(const std::vector<std::wstring>& args) const {
    bool caseSensitive = false;
    std::vector<wchar_t> ignoringSymbols = {};
    std::vector<std::pair<size_t, size_t>> ranges = {};
    int returnCountDiff = -1;
    std::wstring filePaths[2];

    int countPaths = 0;

    for (size_t i = 1; i < args.size(); i++) {
        if (args[i].starts_with(L"--case-sensitive")) {
            caseSensitive = this->parseCaseSensitive(args[i]);
        } else if (args[i].starts_with(L"--ranges")) {
            ranges = this->parseRanges(args[i]);
        } else if (args[i].starts_with(L"--count-diff")) {
            returnCountDiff = this->parseReturnCountDiff(args[i]);
        } else if (args[i].starts_with(L"--ignore-symbol")) {
            ignoringSymbols = this->parseIgnoringSymbols(args[i]);

        } else if (!args[i].starts_with(L"--")) {
            if (2 < countPaths) {
                throw ParserException("Invalid parameters detected. > 2 paths");
            }

            if (!std::filesystem::exists(args[i])) {
                throw ParserException("Invalidate path " + std::string(args[i].begin(), args[i].end()));
            }

            filePaths[countPaths++] = args[i];
        } else {
            throw ParserException("Invalid parameter detected: " + std::string(args[i].begin(), args[i].end()));
        }
    }

    if (countPaths < 2) {
        throw ParserException("Invalid parameters detected. < 2 paths");
    }

    return kdiff::Config(
        std::move(filePaths[0]),
        std::move(filePaths[1]),
        std::move(ranges),
        std::move(ignoringSymbols),
        caseSensitive,
        returnCountDiff);
}

bool Parser::parseCaseSensitive(const std::wstring& arg) const {
    return true;
}

std::vector<std::pair<size_t, size_t>> Parser::parseRanges(const std::wstring& arg) const {
    try {
        const std::wstring command = L"--ranges";
        std::wstring ranges = arg.substr(command.size());

        int posSeporator = ranges.find(L":");
        std::wstring start = ranges.substr(0, posSeporator);
        size_t startFirstFileLine = std::stoul(start.c_str());

        int posEndFirstLineFile = ranges.find(L",");
        std::wstring end = ranges.substr(posSeporator + 1, posEndFirstLineFile - posSeporator);
        size_t endFirstFileLine = std::stoul(end.c_str());

        if (endFirstFileLine < startFirstFileLine) {
            throw ParserException("1 : start < end");
        }

        std::vector<std::pair<size_t, size_t>> result;
        result.emplace_back(startFirstFileLine, endFirstFileLine);

        size_t posSeporator2 = ranges.find(L":", posEndFirstLineFile);
        if (posSeporator2 == std::string::npos) {
            if (posEndFirstLineFile < ranges.size()) {
                throw ParserException("not syntaxsis");
            }

            return result;
        }

        start = ranges.substr(posEndFirstLineFile + 1, ranges.size() - posSeporator2 - 1);
        size_t startSecondFileLine = std::stoul(start.c_str());

        end = ranges.substr(posSeporator2 + 1);
        size_t endSecondFileLine = std::stoul(end.c_str());

        if (endSecondFileLine < startFirstFileLine) {
            throw ParserException("2 : start < end");
        }

        result.emplace_back(startSecondFileLine, endSecondFileLine);

        return result;
    } catch (const ParserException& ex) {
        throw ex;
    }
}

int Parser::parseReturnCountDiff(const std::wstring& arg) const {
    const std::wstring command = L"--count-diff";

    try {
        return std::stoul(arg.substr(command.size()).c_str());
    } catch (const std::exception& ex) {
        throw ParserException("invalidate parametrs --count-diff");
    }
}

// TODO доделай парсинг игнорируемых символов
std::vector<wchar_t> Parser::parseIgnoringSymbols(const std::wstring& arg) const {
    return {};
}

}  // namespace kdiff