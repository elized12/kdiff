#pragma once

#include <iostream>
#include <vector>

#include "kdiff/Difference.hpp"
#include "kdiff/ui/RenderException.hpp"

namespace kdiff {
namespace ui {

class DiffRender {
   protected:
    enum Color : size_t {
        COLOR_RED = 31,
        COLOR_GREEN = 32,
        COLOR_DEFAULT = 39
    };

   public:
    void render(const std::vector<kdiff::Difference>& differances) const;

   private:
    inline void renderAddedLine(const kdiff::Difference& differance) const;
    inline void renderRemoveLine(const kdiff::Difference& differance) const;
    inline void renderCommonLine(const kdiff::Difference& Differance) const;
};

}  // namespace ui
}  // namespace kdiff