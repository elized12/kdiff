#pragma once

#include <exception>
#include <string>

namespace kdiff {
namespace differ {
namespace line {

class RangeException : public std::exception {
   private:
    const std::string _message;

   public:
    RangeException(const std::string& message);

   public:
    const char* what() const noexcept override;
};

}  // namespace line
}  // namespace differ
}  // namespace kdiff