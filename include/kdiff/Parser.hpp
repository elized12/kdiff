#pragma once

#include <string>

#include "kdiff/Config.hpp"

namespace kdiff {

class Parser {
   public:
    Config parseArgs(const std::vector<std::string>& args) const;
};

}  // namespace kdiff