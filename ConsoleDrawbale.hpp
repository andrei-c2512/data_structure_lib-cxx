#pragma once

#include <vector>
#include <string>


class ConsoleDrawable {
public:
	ConsoleDrawable() {
		x = y = 0;
	}
	ConsoleDrawable(int32_t x, int32_t y ,int32_t width, int32_t height) {
		surface.resize(height, std::string(width, ' '));
	}
	ConsoleDrawable(std::vector<std::string> surface0) {
		surface = std::move(surface0);
	}
	void draw(const ConsoleDrawable& drawable) {
		for (int32_t dy = 0; dy < drawable.surface.size(); dy++) {
			for (int32_t dx = 0; dx < drawable[y].size(); dx++) {
				surface[y + dy + drawable.y][x + dx + drawable.x] = drawable[dy][dx];
			}
		}
	}

	const std::string& operator[](int32_t y) const {
		assert(y >= 0 && y < surface.size());
		return surface[y];
	}

	std::string& operator[](int32_t y) {
		assert(y >= 0 && y < surface.size());
		return surface[y];
	}

	int32_t x, y;
	std::vector<std::string> surface;
};