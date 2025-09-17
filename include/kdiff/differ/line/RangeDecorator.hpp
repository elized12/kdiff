#pragma once

#include "kdiff/differ/LineDiffer.hpp"
#include "kdiff/differ/line/LineDifferDecorator.hpp"
#include "kdiff/differ/line/RangeException.hpp"

namespace kdiff {
namespace differ {
namespace line {

class RangeDecorator : public kdiff::differ::line::LineDifferDecorator {
   public:
    RangeDecorator(std::unique_ptr<kdiff::differ::LineDiffer> differ);
    virtual ~RangeDecorator() = default;

   protected:
    virtual void preprocessingFirstFileStream(const std::unique_ptr<std::wfstream>& fileStream);
    virtual void preprocessingSecondFileStream(const std::unique_ptr<std::wfstream>& fileStream);
    virtual bool checkStopConditionFirstStream(int lineNumber, const std::wstring& line) override;
    virtual bool checkStopConditionSecondStream(int lineNumber, const std::wstring& line) override;
};

}  // namespace line
}  // namespace differ
}  // namespace kdiff