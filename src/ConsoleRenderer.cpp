#include "ConsoleRenderer.hpp"



namespace TinyDS{
    ConsoleRenderer::ConsoleRenderer() {
        surface.surface.resize(height, std::string(width, ' '));
    }
    void ConsoleRenderer::render() {
            system("CLS");
            std::stringstream output;
            for (int32_t y = 0; y < surface.surface.size(); y++) {
                    output << surface[y] << '\n';
            }
            std::cout << output.str() << std::endl;
    }

    void ConsoleRenderer::draw(const ConsoleDrawable& drawable) {
        surface.draw(drawable);
    }
    void ConsoleRenderer::draw(const DrawableNode<int>& node) {
        surface.draw(node.drawable);
    }
}
