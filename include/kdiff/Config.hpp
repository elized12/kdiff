#pragma once
#include <vector>

namespace kdiff {

class Config {
   private:
    std::vector<std::pair<size_t, size_t>> _ranges;
    std::vector<wchar_t> _ignoringSymbols;
    bool _caseSensitive;
    int _returnCountDiff;

   public:
    Config(
        const std::vector<std::pair<size_t, size_t>> ranges,
        const std::vector<wchar_t> ignoringSymbols,
        bool caseSensitive = false,
        int returnCountDiff = -1);

   public:
    std::vector<std::pair<size_t, size_t>> getRanges() const;
    bool getCaseSensitive() const;
    int getReturnCountDiff() const;
    std::vector<wchar_t> getIgnoringSymbols() const;
};

}  // namespace kdiff