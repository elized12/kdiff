#pragma once

#include "kdiff/_detail/algorithm/BaseDiff.hpp"

namespace kdiff {
namespace _detail {
namespace algorithm {

class BaseDiffDecorator : public BaseDiff {
   protected:
    std::unique_ptr<BaseDiff> _parent;

   public:
    BaseDiffDecorator(std::unique_ptr<BaseDiff> parent);
};

}  // namespace algorithm
}  // namespace _detail
}  // namespace kdiff