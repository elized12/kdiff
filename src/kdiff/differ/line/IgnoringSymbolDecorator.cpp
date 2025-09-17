#include "kdiff/differ/line/IgnoringSymbolDecorator.hpp"

namespace kdiff {
namespace differ {
namespace line {

IgnoringSymbolDecorator::IgnoringSymbolDecorator(std::unique_ptr<kdiff::differ::LineDiffer> differ)
    : LineDifferDecorator(std::move(differ)) {
    this->_ignoringSymbols = this->_config.getIgnoringSymbols();

    std::sort(this->_ignoringSymbols.begin(), this->_ignoringSymbols.end());
}

void IgnoringSymbolDecorator::processLine(std::wstring& line) {
    line.erase(
        std::remove_if(
            line.begin(),
            line.end(),
            [this](wchar_t symbol) { return std::binary_search(this->_ignoringSymbols.begin(), this->_ignoringSymbols.end(), symbol); }),
        line.end());

    this->_parent->processLine(line);
}

}  // namespace line
}  // namespace differ
}  // namespace kdiff