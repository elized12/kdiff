#include "kdiff/differ/line/CaseSensitiveDecorator.hpp"

namespace kdiff {
namespace differ {
namespace line {

CaseSensitiveDecorator::CaseSensitiveDecorator(std::unique_ptr<kdiff::differ::LineDiffer> differ) : LineDifferDecorator(std::move(differ)) {
}

void CaseSensitiveDecorator::processLine(std::wstring& line) {
    for (size_t i = 0; i < line.size(); i++) {
        line[i] = std::towlower(line[i]);
    }

    return this->_parent->processLine(line);
}

}  // namespace line
}  // namespace differ
}  // namespace kdiff