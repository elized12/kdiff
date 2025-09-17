#include "kdiff/Config.hpp"

namespace kdiff {

Config::Config(
    std::wstring&& filePath1,
    std::wstring&& filePath2,
    std::vector<std::pair<size_t, size_t>>&& ranges,
    std::vector<wchar_t>&& ignoringSymbols,
    bool caseSensitive,
    int returnCountDiff)
    : _ranges(std::move(ranges)),
      _ignoringSymbols(std::move(ignoringSymbols)),
      _caseSensitive(std::move(caseSensitive)),
      _returnCountDiff(std::move(returnCountDiff)),
      _filePath1(std::move(filePath1)),
      _filePath2(std::move(filePath2)) {
}

std::vector<std::pair<size_t, size_t>> Config::getRanges() const {
    return this->_ranges;
}

bool Config::getCaseSensitive() const {
    return this->_caseSensitive;
}

int Config::getReturnCountDiff() const {
    return this->_returnCountDiff;
}

std::vector<wchar_t> Config::getIgnoringSymbols() const {
    return this->_ignoringSymbols;
}

std::wstring Config::getFilePath1() const {
    return this->_filePath1;
}

std::wstring Config::getFilePath2() const {
    return this->_filePath2;
}

}  // namespace kdiff