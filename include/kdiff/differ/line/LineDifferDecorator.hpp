#pragma once

#include "kdiff/differ/LineDiffer.hpp"

namespace kdiff {
namespace differ {
namespace line {

class LineDifferDecorator : public LineDiffer {
   protected:
    std::unique_ptr<kdiff::differ::LineDiffer> _parent;

   public:
    LineDifferDecorator(std::unique_ptr<kdiff::differ::LineDiffer> differ);
    virtual ~LineDifferDecorator() = default;
};

}  // namespace line
}  // namespace differ
}  // namespace kdiff