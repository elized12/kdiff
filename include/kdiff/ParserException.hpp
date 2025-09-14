#pragma once

#include <exception>
#include <string>

namespace kdiff {

class ParserException : public std::exception {
   private:
    const std::string _message;

   public:
    ParserException(const std::string& message);

   public:
    const char* what() const noexcept override;
};

}  // namespace kdiff