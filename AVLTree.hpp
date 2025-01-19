#include "TreeNode.hpp"
#include "TreeUtility.hpp"
#include "TreeInterface.hpp"
#include <stack>


namespace Tree {
	template<typename T>
	class AVLTree : public SearchTreeInterface<T> {
	public:
		AVLTree() = default;
		AVLTree(AVLNode<T>* root0)
			:root(root0)
		{}

		void insert(const T& val) override {
			if (root == nullptr) {
				root = new AVLNode<T>(val);
				return;
			}


			AVLNode<T>* last = nullptr;
			AVLNode<T>* cur = root;

			std::stack<AVLNode<T>*> trail;

			while (cur != nullptr) {
				trail.push(cur);

				last = cur;
				if (cur->val < val) {
					cur = cur->right;
				}
				else
					cur = cur->left;
			}

			// pop off the last element in the stack because it's bf is always between -1 and 1
			trail.pop();
			if (last->val < val) {
				last->right = new AVLNode<T>(val);
			}
			else
				last->left = new AVLNode<T>(val);


			
			balance(val);
		}
		//return nullptr if not found
		TreeNode<T>* search(const T& val) override {
			AVLNode<T>* cur = root;
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

	private:
		void balance(const T& val) {
			root->balanceFactor = Utility::height(root->left) - Utility::height(root->right);

			while (validBF(root->balanceFactor) == false) {
				if (unbalancedRight()) {
					//if the tree is unbalanced to the right and the unbalance is by having a straight line to the left
					if (val < root->left->val) {
						//if you rotate right , you give more load to the right side , therefore balancing it
						rotateRight(root);
					}
					else
					{
						rotateLeft(root->left, , root);
						rotateRight(root);
					}
				}
				//if the tree is unbalanced to the left and it's unbalanced in a straight line
				else if (unbalancedLeft()) {
					//check if it's a straight line unbalance
					if (val > root->right->val) {
						rotateRight(root);
					}
					//otherwise it's a wedge like this '>'
					else {
						rotateRight(root->right, root);
						rotateLeft(root);
					}
				}
				root->balanceFactor = Utility::height(root->left) - Utility::height(root->right);
			}
		}
		static bool validBF(int8_t factor) {
			return factor >= -1 && factor <= 1;
		}
		static void rotateLeft(AVLNode<T>*& root) {
			//mai intai root nu mai e parintele lui ala din dreapta
			// dupa aia ala din dreapta are membru stang fosta radacina
			//dupa aia subarborele drept al fostului parinte devine ce avea subaorborele drept in stanga lui
			// subarborele drept devine parintele fostei radacini , adica , radacina

			AVLNode<T>* rightSubtree = root->right;
			root->right = rightSubtree->left;
			rightSubtree->left = root;
			root = rightSubtree;
		}
		static void rotateLeft(AVLNode<T>*& node , AVLNode<T>*& parent) {
			//mai intai root nu mai e parintele lui ala din dreapta
			// dupa aia ala din dreapta are membru stang fosta radacina
			//dupa aia subarborele drept al fostului parinte devine ce avea subaorborele drept in stanga lui
			// subarborele drept devine parintele fostei radacini , adica , radacina

			AVLNode<T>* rightSubtree = node->right; // store the right side
			node->right = rightSubtree->left;       //the node takes ownership of the right subtrees left 
			rightSubtree->left = node;			    // now the right subtree owns the left
			parent->left = rightSubtree;			// reassigning the orignal nodes parent
		}
		static void rotateRight(AVLNode<T>*& root) {
			AVLNode<T>* leftSubtree = root->left;
			root->left = leftSubtree->right;
			leftSubtree->right = root;
			root = leftSubtree;
		}
		static void rotateRight(AVLNode<T>*& node , AVLNode<T>*& parent) {
			AVLNode<T>* leftSubtree = node->left;
			node->left = leftSubtree->right;
			leftSubtree->right = node;
			parent->right = leftSubtree;
		}


		bool unbalancedRight() const noexcept{
			return root->balanceFactor > 1;
		}
		bool unbalancedLeft() const noexcept {
			return root->balanceFactor < -1;
		}
	private:
		AVLNode<T>* root = nullptr;
	};
}