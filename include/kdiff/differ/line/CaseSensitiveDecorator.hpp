#pragma once

#include "kdiff/differ/LineDiffer.hpp"
#include "kdiff/differ/line/LineDifferDecorator.hpp"
#include "kdiff/differ/line/RangeException.hpp"

namespace kdiff {
namespace differ {
namespace line {

class CaseSensitiveDecorator : public kdiff::differ::line::LineDifferDecorator {
   public:
    CaseSensitiveDecorator(std::unique_ptr<kdiff::differ::LineDiffer> differ);
    virtual ~CaseSensitiveDecorator() = default;

   protected:
    virtual void processLine(std::wstring& line) override;
};

}  // namespace line
}  // namespace differ
}  // namespace kdiff