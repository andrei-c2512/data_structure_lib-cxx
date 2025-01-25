#pragma once
#include "DrawableNode.hpp"
#include <iostream>
#include "TreeNode.hpp"
#include <sstream>

class ConsoleRenderer {
public:
	ConsoleRenderer() {
		surface.surface.resize(height, std::string(width, ' '));
	}
	void render() {
		system("CLS");
		std::stringstream output;
		for (int32_t y = 0; y < surface.surface.size(); y++) {
			output << surface[y] << '\n';
		}
		std::cout << output.str() << std::endl;
	}

	void draw(Tree::TreeNode<int>* root) {
		int treeHeight = Tree::Utility::height(root);
		int nodeSpacing = 3;

		int nLastLevel = pow(2, treeHeight - 1);
		int totalWidth = nLastLevel * DrawableNode<int>::width - (nLastLevel - 1) * nodeSpacing;
		
		int startX = 0, i = treeHeight;
		int startY = 0;
		auto onStartLevel = [&startX, &startY ,  &i, treeHeight, totalWidth , nodeSpacing]() {
			int nLevel = pow(2, treeHeight - i);
			int levelWidth = nLevel * DrawableNode<int>::width - (nLevel - 1) * nLevel;
			startX = (totalWidth - levelWidth) / 2;
			startY += DrawableNode<int>::height + nodeSpacing;
			i--;
		};

		auto onNode = [this , &startY ,  &startX , nodeSpacing](Tree::TreeNode<int>* node) {
			if (node) {
				draw(DrawableNode(startX , startY , node->val));
			}
			startX += DrawableNode<int>::width + nodeSpacing;
		};
		Tree::Utility::levelTraversalWithNull<int>(root,  onNode , onStartLevel);

	}
	void draw(const ConsoleDrawable& drawable) {
		surface.draw(drawable);
	}
	void draw(const DrawableNode<int>& node) {
		surface.draw(node.drawable);
	}
private:
	ConsoleDrawable surface;
	static constexpr int width = 200;
	static constexpr int height = 200;
};