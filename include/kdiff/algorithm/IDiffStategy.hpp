#pragma once

#include <string>
#include <vector>

#include "kdiff/Config.hpp"
#include "kdiff/Difference.hpp"

namespace kdiff {
namespace algorithm {

class IDiffStategy {
   public:
    virtual ~IDiffStategy() = default;

   public:
    virtual std::vector<kdiff::Difference> getDifferences(
        const kdiff::Config& config,
        std::vector<std::wstring>& fileLines1,
        std::vector<std::wstring>& fileLines2) const = 0;
};

}  // namespace algorithm
}  // namespace kdiff
