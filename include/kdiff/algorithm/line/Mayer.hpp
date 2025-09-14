#pragma once

#include <algorithm>
#include <unordered_map>

#include "kdiff/algorithm/IDiffStategy.hpp"

namespace kdiff {
namespace algorithm {
namespace line {

class Mayer : public IDiffStategy {
   public:
    std::vector<kdiff::Difference> getDifferences(
        const kdiff::Config& config,
        std::vector<std::wstring>& fileLines1,
        std::vector<std::wstring>& fileLines2) const override;

   protected:
    bool isQualLine(const std::wstring& line1, size_t hash1, const std::wstring& line2, size_t hash2) const;
    std::vector<kdiff::Difference> backtrack(
        const std::vector<std::unordered_map<long long, long long>>&,
        std::vector<std::wstring>& fileLines1,
        std::vector<std::wstring>& fileLines2,
        long long countEdits,
        const std::vector<size_t>& hashes1,
        const std::vector<size_t>& hashes2) const;
};

}  // namespace line
}  // namespace algorithm
}  // namespace kdiff