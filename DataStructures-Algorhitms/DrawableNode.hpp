#pragma once
#include "ConsoleDrawbale.hpp"
#include <algorithm>

//this shi dangerous cause I ain't testing for other data structures yet
template<typename T>
struct DrawableNode {
    DrawableNode(int32_t x, int32_t  y , T val)
        :DrawableNode(val)
    {
        drawable.x = x;
        drawable.y = y;
    }
    DrawableNode(T val) {
        drawable.surface = defaultMatrix();

        std::string str = std::to_string(val);

        int i;
        for (i = 0; i < std::min(int16_t(width - spacing - borderWidth), (int16_t)str.size()); i++) {
            drawable[height / 2][i + spacing + borderWidth] = str[i];
        }
    }
    static std::vector<std::string> defaultMatrix() {
        return { {" /------\\ "} ,
                 {"/        \\"},
                 {"|         |"},
                 {"\\        /"},
                 {" \\------/ "} };
    }

    int16_t x = 0, y = 0;
    static constexpr int width = 10 , height = 5;
    static constexpr int spacing = 1;
    static constexpr int borderWidth = 1;
    ConsoleDrawable drawable;
};