#pragma once

#include <string>

namespace kdiff {

class Difference {
   public:
    enum class DiffType : short {
        ADDED,
        DELETED,
        UNCHANGED
    };

   private:
    std::wstring _value;
    DiffType _info;

   public:
    Difference(const std::wstring& value = L"", const DiffType& info = DiffType::UNCHANGED);
    Difference(std::wstring&& value, const DiffType& info = DiffType::UNCHANGED);

   public:
    const std::wstring& getValue() const;
    const DiffType& getType() const;
};

}  // namespace kdiff