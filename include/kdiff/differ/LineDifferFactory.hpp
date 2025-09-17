#pragma once

#include <memory>

#include "kdiff/differ/LineDiffer.hpp"
#include "kdiff/differ/line/CaseSensitiveDecorator.hpp"
#include "kdiff/differ/line/IgnoringSymbolDecorator.hpp"
#include "kdiff/differ/line/RangeDecorator.hpp"

namespace kdiff {
namespace differ {

class LineDifferFactory {
   public:
    std::unique_ptr<kdiff::differ::LineDiffer> create(
        const Config& config,
        std::unique_ptr<std::wfstream> fileStream1,
        std::unique_ptr<std::wfstream> fileStream2) const;
};

}  // namespace differ
}  // namespace kdiff