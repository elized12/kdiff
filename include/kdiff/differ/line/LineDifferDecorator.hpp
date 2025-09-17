#pragma once

#include <memory>

#include "kdiff/differ/LineDiffer.hpp"

namespace kdiff {
namespace differ {
namespace line {

class LineDifferDecorator : public kdiff::differ::LineDiffer {
   protected:
    std::unique_ptr<kdiff::differ::LineDiffer> _parent;

   public:
    LineDifferDecorator(std::unique_ptr<kdiff::differ::LineDiffer> differ);
    virtual ~LineDifferDecorator() = default;

   public:
    virtual void preprocessingFirstFileStream(const std::unique_ptr<std::wfstream>& fileStream);
    virtual void preprocessingSecondFileStream(const std::unique_ptr<std::wfstream>& fileStream);
    virtual void processLine(std::wstring& line);
    virtual bool checkStopConditionFirstStream(int lineNumber, const std::wstring& line);
    virtual bool checkStopConditionSecondStream(int lineNumber, const std::wstring& line);
};

}  // namespace line
}  // namespace differ
}  // namespace kdiff