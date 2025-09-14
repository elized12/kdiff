#pragma once

#include <filesystem>
#include <string>

#include "kdiff/Config.hpp"
#include "kdiff/ParserException.hpp"

namespace kdiff {

class Parser {
   public:
    Config parseArgs(const std::vector<std::wstring>& args) const;

   private:
    bool parseCaseSensitive(const std::wstring& arg) const;
    std::vector<std::pair<size_t, size_t>> parseRanges(const std::wstring& arg) const;
    int parseReturnCountDiff(const std::wstring& arg) const;
    std::vector<wchar_t> parseIgnoringSymbols(const std::wstring& arg) const;
};

}  // namespace kdiff