#pragma once
#include "TreeNode.hpp"
#include "TreeInterface.hpp"
#include <assert.h>
#include <stack>


namespace Tree {
	template<typename T , typename A = T>
	class RedBlackTree : public AbstractSearchTree<T , A> {
	public:
		RedBlackTree() = default;
		void insert(const A& val) override { 
			if (root == nullptr) {
				root = new RedBlackTreeNode<T>(val , NodeColor::BLACK);
			}
			RedBlackTreeNode<T>* last = nullptr;
			RedBlackTreeNode<T>* cur = root;

			std::stack<RedBlackTreeNode<T>*> stackTrace;
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
				last->right = new RedBlackTreeNode<T>(val , NodeColor::RED);
			}
			else
				last->left = new RedBlackTreeNode<T>(val, NodeColor::RED);

			//now we will keep track of the current node , parent  , and grandparent(if we know the grandparent , we also know the uncle)
			RedBlackTree<T>* current = stackTrace.top();
			stackTrace.pop();
			RedBlackTree<T>* parent      = stackTrace.top();
			stackTrace.pop();
			RedBlackTree<T>* grandparent = stackTrace.top();
			stackTrace.pop();

			while (grandparent) {

				for (int8_t i = 0; i < 3; i++) {
					if (trainCheck[i](current, parent, grandparent , getUncle(parent , grandparent))) {
						break;
					}
				}


			}

		}
		static bool redUncleCase(RedBlackTreeNode<T>*& current, RedBlackTreeNode<T>*& parent, RedBlackTreeNode<T>*& grandparent , RedBlackTreeNode<T>*& uncle) {
			if (uncle->color != NodeColor::RED) {
				return false;
			}
			else {
				uncle->color = NodeColor::BLACK;
				grandparent->color = parent->color = NodeColor::RED;
			}
		}

		static bool blackUncleTriangleCase(RedBlackTreeNode<T>*& current, RedBlackTreeNode<T>*& parent, RedBlackTreeNode<T>*& grandparent, RedBlackTreeNode<T>*& uncle) {
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
		static bool blackUncleLinearCase(RedBlackTreeNode<T>*& current, RedBlackTreeNode<T>*& parent, RedBlackTreeNode<T>*& grandparent, RedBlackTreeNode<T>*& uncle) {
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

		static RedBlackTreeNode<T>* getUncle(RedBlackTreeNode<T>*& parent, RedBlackTreeNode<T>*& grandparent) {
			if (parent->val < grandparent->val)
				return grandparent->right;
			else
				return grandparent->left;
		}

		using AbstractSearchTree<T, A>::rotateLeft;
		using AbstractSearchTree<T, A>::rotateRight;
	private:
		RedBlackTreeNode<T>* root = nullptr;

		static constexpr std::array<bool(*)(RedBlackTreeNode<T>*&, RedBlackTreeNode<T>*&, RedBlackTreeNode<T>*&, RedBlackTreeNode<T>*&), 3> 
			trainCheck = { &redUncleCase , &blackUncleTriangleCase , &blackUncleLinearCase };
	};
}
