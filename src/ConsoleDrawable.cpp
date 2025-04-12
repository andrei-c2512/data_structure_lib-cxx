#include "ConsoleDrawable.hpp"            
#include <assert.h>


namespace TinyDS{
    ConsoleDrawable::ConsoleDrawable() {
        x = y = 0;
    }
    ConsoleDrawable::ConsoleDrawable(int32_t x0, int32_t y0 ,int32_t width, int32_t height) 
            :x(x0) , y(y0)
    {
            surface.resize(height, std::string(width, ' '));
    }
    ConsoleDrawable::ConsoleDrawable(std::vector<std::string> surface0) {
            surface = std::move(surface0);
    }
    void ConsoleDrawable::draw(const ConsoleDrawable& drawable) {
            for (int32_t dy = 0; dy < drawable.surface.size(); dy++) {
                    for (int32_t dx = 0; dx < drawable[y].size(); dx++) {
                            surface[y + dy + drawable.y][x + dx + drawable.x] = drawable[dy][dx];
                    }
            }
    }

    const std::string& ConsoleDrawable::operator[](int32_t y) const {
            assert(y >= 0 && y < surface.size());
            return surface[y];
    }

    std::string& ConsoleDrawable::operator[](int32_t y) {
            assert(y >= 0 && y < surface.size());
            return surface[y];
    }
}

