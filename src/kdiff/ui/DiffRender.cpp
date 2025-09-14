#include "kdiff/ui/DiffRender.hpp"

namespace kdiff {
namespace ui {

void DiffRender::render(const std::vector<kdiff::Difference>& differances) const {
    for (size_t i = 0; i < differances.size(); i++) {
        switch (differances[i].getType()) {
            case kdiff::Difference::DiffType::ADDED:
                this->renderAddedLine(differances[i]);
                break;
            case kdiff::Difference::DiffType::DELETED:
                this->renderRemoveLine(differances[i]);
                break;
            case kdiff::Difference::DiffType::UNCHANGED:
                this->renderCommonLine(differances[i]);
                break;
            default:
                throw RenderException("not type differences");
                break;
        }
    }
}

inline void DiffRender::renderAddedLine(const kdiff::Difference& difference) const {
    std::wcout << L"\033[" << this->COLOR_GREEN << L"m" << L"+ " << difference.getValue() << std::endl;
}

inline void DiffRender::renderRemoveLine(const kdiff::Difference& difference) const {
    std::wcout << L"\033[" << this->COLOR_RED << L"m" << L"- " << difference.getValue() << std::endl;
}

inline void DiffRender::renderCommonLine(const kdiff::Difference& difference) const {
    std::wcout << L"\033[" << this->COLOR_DEFAULT << L"m" << difference.getValue() << std::endl;
}

}  // namespace ui
}  // namespace kdiff