#pragma once
#include "TreeNode.hpp"

namespace TinyDS::Tree {
	template<typename T>
	class BinarySearchTree {
	public:
		void addNode(TreeNode<T>* node) {
			if (root == nullptr)
			{
				root = node;
				return;
			}

			TreeNode<T>* last = nullptr;
			TreeNode<T>* current = root;
			while (current) {
				last = current;
				if (current->val > node->val) {
					current = current->left;
				}
				else {
					current = current->right;
				}
			}

			if (last->val > node->val) {
				last->left = node;
			}
			else {
				last->right = node;
			}
		}
		void removeNode(Treenode<T>* node);
	private:
		TreeNode<T>* root;
	};

}
