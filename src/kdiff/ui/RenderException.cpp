#include "kdiff/ui/RenderException.hpp"

namespace kdiff {
namespace ui {

RenderException::RenderException(const std::string& message) : _message(_message) {
}

const char* RenderException::what() const noexcept {
    return _message.c_str();
}

}  // namespace ui
}  // namespace kdiff