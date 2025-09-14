#pragma once

#include <vector>

#include "kdiff/Difference.hpp"
#include "kdiff/algorithm/IDiffStategy.hpp"

namespace kdiff {
namespace differ {

class IDiffer {
   public:
    ~IDiffer() = default;

   public:
    virtual std::vector<kdiff::Difference> getDifferences() = 0;

   protected:
    virtual std::unique_ptr<kdiff::algorithm::IDiffStategy> createDiffStrategy() const = 0;
};

}  // namespace differ
}  // namespace kdiff