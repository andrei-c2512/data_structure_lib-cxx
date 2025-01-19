#pragma once
#include "TreeNode.hpp"
#include "TreeInterface.hpp"
#include <assert.h>

namespace Tree {
	enum class NodeColor : int8_t{
		RED = 0x0, BLACK = 0x1
	};


	template<typename T>
	class RedBlackTree : public TreeInterface<T> {
	public:
		RedBlackTree() = default;
		void add(const T& val) override { 
			if (root == nullptr) {
				root = new RedBlackTreeNode<T>()
			}
			RedBlackTreeNode<T>* last = nullptr;
			RedBlackTreeNode<T>* cur = root;

			while (cur != nullptr) {
				last = cur;
				if (cur->val < val) {
					cur = cur->right;
				}
				else
					cur = cur->left;
			}

			if (last->val < val) {
				last->right = new RedBlackTreeNode<T>(val);
			}
			else
				last->left = new RedBlackTreeNode<T>(val);
		}
	private:
	private:
		RedBlackTreeNode<T>* root = nullptr;
	};
}
