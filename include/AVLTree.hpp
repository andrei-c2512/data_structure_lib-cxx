#pragma once

#include "TreeNode.hpp"
#include "TreeUtility.hpp"
#include "TreeInterface.hpp"
#include <stack>
#include <queue>

namespace TinyDS::Tree {

	//I know the order here is different vs the one in Abstract Search Tree. That is because I find it more probable to use your own allocator than to use
	// an adapter
	template<typename T,  typename A = T>
	class AVLTree : public AbstractSearchTree<T , AVLTag , A> {
	public:
		using AbstractSearchTree<T, AVLTag, A>::allocator;
		using AbstractSearchTree<T, AVLTag, A>::getAllocator;
		AVLTree() = default;
		AVLTree(AllocatorInterface* allocator)
			:AbstractSearchTree<T, AVLTag , A>(allocator)
		{}
		AVLTree(TreeNode<T, AVLTag>* root0)
			:root(root0)
		{}
		virtual ~AVLTree() {
			if (root == nullptr)
				return;
			std::stack<TreeNode<T, AVLTag>*> stack;
			std::queue<TreeNode<T, AVLTag>*> q;
			q.push(root);

			while (q.empty() == false) {
				TreeNode<T, AVLTag>* node = q.front();
				stack.push(node);
				q.pop();

				if (node->left)
					q.push(node->left);
				if (node->right)
					q.push(node->right);
			}

			while (stack.empty() == false) {
				TreeNode<T, AVLTag>* n = stack.top();
				allocator->deallocate(n);

				stack.pop();
			}

			root = nullptr;
		}
		void insert(const A& val) override {
			if (root == nullptr) {
				root = new (allocator->allocateBlock()) TreeNode<T, AVLTag>(val);
				return;
			}


			TreeNode<T, AVLTag>* last = nullptr;
			TreeNode<T, AVLTag>* cur = root;

			std::stack<TreeNode<T, AVLTag>*> trail;

			while (cur != nullptr) {
				trail.push(cur);

				last = cur;
				if (cur->val > val) {
					cur = cur->left;
				}
				else
					cur = cur->right;
			}

			if (last->val < val) {
				last->right = new (allocator->allocateBlock()) TreeNode<T, AVLTag>(val);
			}
			else {
				last->left = new (allocator->allocateBlock()) TreeNode<T, AVLTag>(val);
			}


			while (trail.empty() == false) {
				TreeNode<T, AVLTag>* node = trail.top();
				trail.pop();

				if (!trail.empty()) {
					balance(node, trail.top(), val);
				}
				else {
					balance(root, val);
				}
			}
		}
		//return nullptr if not found
		TreeNode<T, AVLTag>* search(const A& val) const noexcept override  {
			TreeNode<T, AVLTag>* cur = root;
			while (cur) {
				if (cur->val > val) {
					cur = cur->left;
				}
				else if (cur->val < val) {
					cur = cur->right;
				}
				else
					return cur;
			}
			return nullptr;
		}
		[[nodiscard]] TreeNode<T, AVLTag>* remove(const A& val) override {
			TreeNode<T, AVLTag>* last = nullptr;
			TreeNode<T, AVLTag>* cur = root;

			while (cur) {
				if (cur->val > val) {
					last = cur;
					cur = cur->left;
				}
				else if (cur->val < val) {
					last = cur;
					cur = cur->right;
				}
				else {
					Utility::detachNode(cur, last);
					return cur;
				}
			}
			return nullptr;
		}
		void erase(const A& val) override {
			TreeNode<T, AVLTag>* node = remove(val);
			if (node) {
				allocator->deallocate((void*)node);
			}
		}
	private:
		void balance(TreeNode<T, AVLTag>*& root, TreeNode<T, AVLTag>*& parent, const A& val) {
			using namespace Utility;
			updateBF(root);

			while (validBF(root->balanceFactor) == false) 
			{
				if (unbalancedLeft(root)) {
					//if the tree is unbalanced to the right and the unbalance is by having a straight line to the left
					//if the left node doesn't exist then it's clearly a wedge imbalance
					if (root->left && val < root->left->val) {
						//if you rotate right , you give more load to the right side , therefore balancing it
						rotateRight(root, parent);
					}
					else
					{
						rotateLeft(root->left, root);
						rotateRight(root, parent);
					}
				}
				//if the tree is unbalanced to the left and it's unbalanced in a straight line
				else if (unbalancedRight(root)) {
					//check if it's a straight line unbalance
					//if the right node doesn't exit then it's clearly a wedge formation
					if (root->right && val > root->right->val) {
						rotateLeft(root, parent);
					}
					//otherwise it's a wedge like this '>'
					else {
						rotateRight(root->right, root);
						rotateLeft(root, parent);
					}
				}
				updateBF(root);
			}
		}
		void balance(TreeNode<T, AVLTag>*& node, const A& val) {
			using namespace Utility;
			updateBF(root);

			while (validBF(root->balanceFactor) == false) 
			{
				if (unbalancedRight(node)) {
					//if the tree is unbalanced to the right and the unbalance is by having a straight line to the right
					if (node->right && val > node->right->val) {
						//if you rotate right , you give more load to the right side , therefore balancing it
						rotateLeft(node);
					}
					else
					{
						Utility::rotateRight(node->right, node);
						rotateLeft(node);
					}
				}
				//if the tree is unbalanced to the left and it's unbalanced in a straight line
				else if (unbalancedLeft(node)) {
					//check if it's a straight line unbalance
					if (node->left != nullptr && val < node->left->val) {
						rotateRight(node);
					}
					//otherwise it's a wedge like this '>'
					else {
						rotateLeft<TreeNode<T, AVLTag>>(node->left, node);
						rotateRight(node);
					}
				}
				updateBF(root);
			}
		}

		static bool validBF(int8_t factor) {
			return factor >= -1 && factor <= 1;
		}


		static bool unbalancedRight(const TreeNode<T , AVLTag>* const node) noexcept {
			return node->balanceFactor < -1;
		}
		static bool unbalancedLeft(const TreeNode<T, AVLTag>* const node) noexcept {
			return node->balanceFactor > 1;
		}

		static void updateBF(TreeNode<T, AVLTag>* node) noexcept {
			node->balanceFactor = int8_t(Utility::height(node->left) - Utility::height(node->right));
		}
	public:
		TreeNode<T, AVLTag>* root = nullptr;
	};
}
