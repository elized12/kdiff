#pragma once

#include <string>

namespace kdiff {

class Differance {
   public:
    enum class DiffType : short {
        ADDED,
        DELETED,
        UNCHANGED
    };

   private:
    std::string _line;
    DiffType _info;
    int _oldLineNumber;
    int _newLineNumber;

   public:
    Differance(const std::string& line = "",
               const DiffType& info = DiffType::UNCHANGED,
               int oldNumberLine = -1,
               int newNumberLine = -1);
};

}  // namespace kdiff