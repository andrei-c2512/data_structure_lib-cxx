#pragma once

#include <vector>
#include <string>


namespace TinyDS{
    class ConsoleDrawable {
    public:
            ConsoleDrawable();
            ConsoleDrawable(int32_t x0, int32_t y0 ,int32_t width, int32_t height);
            ConsoleDrawable(std::vector<std::string> surface0);
            void draw(const ConsoleDrawable& drawable);
            const std::string& operator[](int32_t y) const;
            std::string& operator[](int32_t y);

            int32_t x, y;
            std::vector<std::string> surface;
    };
}
