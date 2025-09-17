#pragma once

#include <string>
#include <vector>

namespace kdiff {

class Config {
   private:
    std::vector<std::pair<size_t, size_t>> _ranges;
    std::vector<wchar_t> _ignoringSymbols;
    bool _caseSensitive;
    int _returnCountDiff;
    std::wstring _filePath1;
    std::wstring _filePath2;

   public:
    Config(
        std::wstring&& filePath1,
        std::wstring&& filePath2,
        std::vector<std::pair<size_t, size_t>>&& ranges,
        std::vector<wchar_t>&& ignoringSymbols,
        bool caseSensitive = false,
        int returnCountDiff = -1);

   public:
    std::vector<std::pair<size_t, size_t>> getRanges() const;
    bool getCaseSensitive() const;
    int getReturnCountDiff() const;
    std::vector<wchar_t> getIgnoringSymbols() const;
    std::wstring getFilePath1() const;
    std::wstring getFilePath2() const;
};

}  // namespace kdiff