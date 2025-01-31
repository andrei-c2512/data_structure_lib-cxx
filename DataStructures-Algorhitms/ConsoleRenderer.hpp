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
	template <typename Tag>
	void draw(Tree::TreeNode<int , Tag>* root) {
		int treeHeight = Tree::Utility::height(root);
		int nodeSpacingX = 3;
		int nodeSpacingY = 3;

		int nLastLevel = pow(2, treeHeight - 1);
		int totalWidth = nLastLevel * DrawableNode<int>::width - (nLastLevel - 1) * nodeSpacingX;
		
		int startX = 0, i = treeHeight , j = 0;
		int startY = 0;
		auto onStartLevel = [&startX, &startY , &j ,  &i, treeHeight, totalWidth , &nodeSpacingX , nodeSpacingY]() {
			nodeSpacingX = DrawableNode<int>::width * Tree::Utility::BSTSSpacingCoeficient(treeHeight , j);
			int nLevel = pow(2, treeHeight - i);
			int levelWidth = nLevel * DrawableNode<int>::width - (nLevel - 1) * nLevel;
			startX = DrawableNode<int>::width * Tree::Utility::BSTStartCoeficient(treeHeight , j);
			startY += DrawableNode<int>::height + nodeSpacingY;
			i--;
			j++;
		};

		auto onNode = [this , &startY ,  &startX , &nodeSpacingX , nodeSpacingY](Tree::TreeNode<int , Tag>* node) {
			if (node) {
				draw(DrawableNode(startX, startY , node->val));
			}
			startX += nodeSpacingX + DrawableNode<int>::width;
		};
		Tree::Utility::levelTraversalWithNull<int , Tag>(root,  onNode , onStartLevel);

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