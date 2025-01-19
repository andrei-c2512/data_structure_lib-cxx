#pragma once
#include "TreeNode.hpp"

namespace Tree {
	namespace Utility{
        template <typename T>
        int height(TreeNode<T>* root) {
            if (root == nullptr) return 0;
            return 1 + std::max(height(root->left), height(root->right));
        }
	}
}