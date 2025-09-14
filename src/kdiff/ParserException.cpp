#include "kdiff/ParserException.hpp"

namespace kdiff {

ParserException::ParserException(
    const std::string& message) : _message(message) {
}

const char* ParserException::what() const noexcept {
    return _message.c_str();
}

}  // namespace kdiff