#pragma once

#include <algorithm>

#include "kdiff/differ/LineDiffer.hpp"
#include "kdiff/differ/line/LineDifferDecorator.hpp"

namespace kdiff {
namespace differ {
namespace line {

class IgnoringSymbolDecorator : public LineDifferDecorator {
   private:
    std::vector<wchar_t> _ignoringSymbols;

   public:
    IgnoringSymbolDecorator(std::unique_ptr<kdiff::differ::LineDiffer> differ);
    virtual ~IgnoringSymbolDecorator() = default;

   public:
    virtual void processLine(std::wstring& line) override;
};

}  // namespace line
}  // namespace differ
}  // namespace kdiff