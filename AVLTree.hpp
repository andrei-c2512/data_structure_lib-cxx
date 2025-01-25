#include "TreeNode.hpp"
#include "TreeUtility.hpp"
#include "TreeInterface.hpp"
#include <stack>
#include <queue>

namespace Tree {
	template<typename T, typename A = T>
	class AVLTree : public AbstractSearchTree<T, A> {
	public:
		AVLTree() = default;
		AVLTree(AVLNode<T>* root0)
			:root(root0)
		{}
		virtual ~AVLTree() {
			std::stack<TreeNode<T>*> stack;
			std::queue<TreeNode<T>*> q;
			q.push(root);

			while (q.empty() == false) {
				TreeNode<T>* node = q.front();
				stack.push(node);
				q.pop();

				if (node->left)
					q.push(node->left);
				if (node->right)
					q.push(node->right);
			}

			while (stack.empty() == false) {
				TreeNode<T>* n = stack.top();
				delete n;

				stack.pop();
			}

			root = nullptr;
		}

		void drawTree() const noexcept {
			//first we calculate the width and the height so that we can arrange them properly
			std::vector<std::string> lineList;
			//breath first search
		}

		void insert(const A& val) override {
			if (root == nullptr) {
				root = new AVLNode<T>(val);
				return;
			}


			TreeNode<T>* last = nullptr;
			TreeNode<T>* cur = root;

			std::stack<AVLNode<T>*> trail;

			while (cur != nullptr) {
				trail.push(static_cast<AVLNode<T>*>(cur));

				last = cur;
				if (cur->val > val) {
					cur = cur->left;
				}
				else
					cur = cur->right;
			}

			// pop off the last element in the stack because it's bf is always between -1 and 1
			trail.pop();
			if (last->val < val) {
				last->right = new AVLNode<T>(val);
			}
			else
				last->left = new AVLNode<T>(val);

			while (trail.empty() == false) {
				AVLNode<T>* node = trail.top();
				trail.pop();

				if (!trail.empty()) {
					balance(node, trail.top(), val);
				}
				else {
					balance(node, val);
				}
			}
		}
		//return nullptr if not found
		TreeNode<T>* search(const A& val) const override {
			TreeNode<T>* cur = root;
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
		[[nodiscard]] TreeNode<T>* remove(const A& val) override {
			TreeNode<T>* last = nullptr;
			TreeNode<T>* cur = root;

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
					detachNode(cur, last);
					return cur;
				}
			}
			return nullptr;
		}
		void erase(const A& val) override {
			TreeNode<T>* node = remove(val);
			if (node) {
				delete node;
			}
		}
	private:
		using AbstractSearchTree<T, A>::rotateLeft;
		using AbstractSearchTree<T, A>::rotateRight;
		using AbstractSearchTree<T, A>::detachNode;

		void balance(AVLNode<T>*& root, AVLNode<T>*& parent, const A& val) {
			root->balanceFactor = Utility::height(root->left) - Utility::height(root->right);

			//while (validBF(root->balanceFactor) == false) 
			{
				if (unbalancedRight()) {
					//if the tree is unbalanced to the right and the unbalance is by having a straight line to the left
					//if the left node doesn't exist then it's clearly a wedge imbalance
					if (root->left && val < root->left->val) {
						//if you rotate right , you give more load to the right side , therefore balancing it
						//rotateRight(root, parent);
					}
					else
					{
						//rotateRight(root->left, root);
						//rotateLeft(root, parent);
					}
				}
				//if the tree is unbalanced to the left and it's unbalanced in a straight line
				else if (unbalancedLeft()) {
					//check if it's a straight line unbalance
					//if the right node doesn't exit then it's clearly a wedge formation
					if (root->right && val > root->right->val) {
						//rotateRight(root, parent);
					}
					//otherwise it's a wedge like this '>'
					else {
						//rotateLeft(root->right, root);
						//rotateRight(root, parent);
					}
				}
				root->balanceFactor = Utility::height(root->left) - Utility::height(root->right);
			}
		}
		void balance(AVLNode<T>*& node, const A& val) {
			node->balanceFactor = Utility::height(node->left) - Utility::height(node->right);

			//while (validBF(node->balanceFactor) == false) 
			{
				if (unbalancedRight()) {
					//if the tree is unbalanced to the right and the unbalance is by having a straight line to the left
					if (node->left && val < node->left->val) {
						//if you rotate right , you give more load to the right side , therefore balancing it
						//rotateRight(root);
					}
					else
					{
						//rotateRight(root->left, root);
						//rotateLeft(root);
					}
				}
				//if the tree is unbalanced to the left and it's unbalanced in a straight line
				else if (unbalancedLeft()) {
					//check if it's a straight line unbalance
					if (node->right != nullptr) {
						if (val > node->right->val) {
							//rotateRight(root);
						}
						//otherwise it's a wedge
						else {

						}
					}
					//otherwise it's a wedge like this '>'
					else {
						//rotateLeft(root->right, root);
						//rotateRight(root);
					}
				}
				node->balanceFactor = Utility::height(node->left) - Utility::height(node->right);
			}
		}

		static bool validBF(int8_t factor) {
			return factor >= -1 && factor <= 1;
		}


		bool unbalancedRight() const noexcept {
			return root->balanceFactor < -1;
		}
		bool unbalancedLeft() const noexcept {
			return root->balanceFactor > 1;
		}
	public:
		AVLNode<T>* root = nullptr;
	};
}
