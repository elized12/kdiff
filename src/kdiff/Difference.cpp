
#include "kdiff/Difference.hpp"

namespace kdiff {

Difference::Difference(const std::wstring& value, const DiffType& info) : _value(value), _info(info) {
}

Difference::Difference(std::wstring&& value, const DiffType& info) : _value(std::move(value)), _info(info) {
}

const std::wstring& Difference::getValue() const {
    return this->_value;
}

const kdiff::Difference::DiffType& Difference::getType() const {
    return this->_info;
}

}  // namespace kdiff