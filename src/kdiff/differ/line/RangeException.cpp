#include "kdiff/differ/line/RangeException.hpp"

namespace kdiff {
namespace differ {
namespace line {

RangeException::RangeException(
    const std::string& message) : _message(message) {
}

const char* RangeException::what() const noexcept {
    return _message.c_str();
}

}  // namespace line
}  // namespace differ
}  // namespace kdiff