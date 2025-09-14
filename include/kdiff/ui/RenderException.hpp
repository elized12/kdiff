#pragma once

#include <exception>
#include <string>

namespace kdiff {
namespace ui {

class RenderException : public std::exception {
   private:
    const std::string _message;

   public:
    RenderException(const std::string& message);

   public:
    const char* what() const noexcept override;
};

}  // namespace ui
}  // namespace kdiff