#pragma once
#include "TreeNode.hpp"
#include "TreeInterface.hpp"
#include <assert.h>
#include <stack>


namespace TinyDS::Tree {
	template<typename T , typename A = T>
	class RedBlackTree : public AbstractSearchTree<T , A , RedBlackTag> {
	public:
		RedBlackTree() = default;
		void insert(const A& val) override { 
			if (root == nullptr) {
				root = new TreeNode<T, RedBlackTag>(val , NodeColor::BLACK);
			}
			TreeNode<T, RedBlackTag>* last = nullptr;
			TreeNode<T, RedBlackTag>* cur = root;

			std::stack<TreeNode<T, RedBlackTag>*> stackTrace;
			while (cur != nullptr) {
				stackTrace.emplace(cur);
				last = cur;
				if (cur->val < val) {
					cur = cur->right;
				}
				else
					cur = cur->left;

			}


			if (last->val < val) {
				last->right = new TreeNode<T, RedBlackTag>(val , NodeColor::RED);
			}
			else
				last->left = new TreeNode<T, RedBlackTag>(val, NodeColor::RED);

			//now we will keep track of the current node , parent  , and grandparent(if we know the grandparent , we also know the uncle)
			TreeNode<T, RedBlackTag>* current = stackTrace.top();
			stackTrace.pop();
			TreeNode<T, RedBlackTag>* parent      = stackTrace.top();
			stackTrace.pop();
			TreeNode<T, RedBlackTag>* grandparent = stackTrace.top();
			stackTrace.pop();

			while (grandparent) {

				for (int8_t i = 0; i < 3; i++) {
					if (trainCheck[i](current, parent, grandparent , getUncle(parent , grandparent))) {
						break;
					}
				}


			}

		}
		static bool redUncleCase(TreeNode<T, RedBlackTag>*& current, TreeNode<T, RedBlackTag>*& parent, TreeNode<T, RedBlackTag>*& grandparent , TreeNode<T, RedBlackTag>*& uncle) {
			if (uncle->color != NodeColor::RED) {
				return false;
			}
			else {
				uncle->color = NodeColor::BLACK;
				grandparent->color = parent->color = NodeColor::RED;
			}
		}

		static bool blackUncleTriangleCase(TreeNode<T, RedBlackTag>*& current, TreeNode<T, RedBlackTag>*& parent, TreeNode<T, RedBlackTag>*& grandparent, TreeNode<T, RedBlackTag>*& uncle) {
			assert(uncle->color == NodeColor::BLACK);

			//checking this kind of wedge: <
			if (grandparent->val > parent->val && current->val > parent->val) {
				rotateLeft(current, parent);
				return blackUncleLinearCase(current, parent, grandparent);
			}
			//checking this kind of wedge: >
			else if (grandparent->val < parent->val && current->val < parent->val) {
				rotateRight(current, parent);
				return blackUncleLinearCase(current , parent , grandparent);
			}



			return false;
		}
		static bool blackUncleLinearCase(TreeNode<T, RedBlackTag>*& current, TreeNode<T, RedBlackTag>*& parent, TreeNode<T, RedBlackTag>*& grandparent, TreeNode<T, RedBlackTag>*& uncle) {
			assert(uncle->color == NodeColor::BLACK);

			//straight line line to the left
			if (grandparent->val > parent->val && parent->val > current->val) {
				rotateLeft(parent, grandparent);
			}
			//straight line to the right
			else if (grandparent->val < parent->val && parent->val < current->val) {
				rotateRight(parent, grandparent);
			}
		}

		static TreeNode<T, RedBlackTag>* getUncle(TreeNode<T, RedBlackTag>*& parent, TreeNode<T, RedBlackTag>*& grandparent) {
			if (parent->val < grandparent->val)
				return grandparent->right;
			else
				return grandparent->left;
		}

		using AbstractSearchTree<T, A>::rotateLeft;
		using AbstractSearchTree<T, A>::rotateRight;
	private:
		TreeNode<T, RedBlackTag>* root = nullptr;

		static constexpr std::array<bool(*)(TreeNode<T, RedBlackTag>*&, TreeNode<T, RedBlackTag>*&, TreeNode<T, RedBlackTag>*&, TreeNode<T, RedBlackTag>*&), 3> 
			trainCheck = { &redUncleCase , &blackUncleTriangleCase , &blackUncleLinearCase };
	};
}
