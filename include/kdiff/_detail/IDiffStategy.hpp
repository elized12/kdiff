#pragma once

#include <vector>

#include "kdiff/Difference.hpp"

namespace kdiff {
namespace _detail {

class IDiffStategy {
   public:
    ~IDiffStategy() = default;

   public:
    virtual std::vector<kdiff::Differance> getDifferances() = 0;
};

}  // namespace _detail
}  // namespace kdiff