#include "kdiff/differ/LineDifferFactory.hpp"

namespace kdiff {
namespace differ {

std::unique_ptr<kdiff::differ::LineDiffer> LineDifferFactory::create(
    const Config& config,
    std::unique_ptr<std::wfstream> fileStream1,
    std::unique_ptr<std::wfstream> fileStream2) const {
    std::unique_ptr<kdiff::differ::LineDiffer> lineDiffer = std::make_unique<kdiff::differ::LineDiffer>(
        config,
        std::move(fileStream1),
        std::move(fileStream2));

    if (config.getCaseSensitive()) {
        lineDiffer = std::make_unique<kdiff::differ::line::CaseSensitiveDecorator>(std::move(lineDiffer));
    }

    if (!config.getIgnoringSymbols().empty()) {
        lineDiffer = std::make_unique<kdiff::differ::line::IgnoringSymbolDecorator>(std::move(lineDiffer));
    }

    if (!config.getRanges().empty()) {
        lineDiffer = std::make_unique<kdiff::differ::line::RangeDecorator>(std::move(lineDiffer));
    }

    return lineDiffer;
}

}  // namespace differ
}  // namespace kdiff