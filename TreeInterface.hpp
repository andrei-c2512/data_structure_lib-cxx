#pragma once
#include "TreeNode.hpp"
#include "TreeUtility.hpp"
#include <concepts>


template<typename T , typename A> 
concept TreeTypeAdapter = std::totally_ordered<T> && std::totally_ordered<A> && requires(T lhs, A rhs) {
	{ lhs < rhs } -> std::convertible_to<bool>;
	{ lhs > rhs } -> std::convertible_to<bool>;
	{ lhs == rhs } -> std::convertible_to<bool>;
};

namespace Tree {
	template<std::totally_ordered dataType , TreeTypeAdapter<dataType> adapter = dataType>
	class TreeInterface {
	public:
		virtual ~TreeInterface() = default;
		virtual void insert(const adapter& val) = 0;
		virtual void erase(const adapter& val) = 0;
		[[nodiscard]] virtual TreeNode<dataType>* remove(const adapter& val) = 0;
	};
	
	template<typename dataType , typename adapter = dataType>
	class AbstractSearchTree : public TreeInterface<dataType , adapter> {
	public:
		virtual ~AbstractSearchTree() = default;
		virtual TreeNode<dataType>* search(const adapter& val) const = 0;
		static void rotateLeft(TreeNode<dataType>*& root) {
			//mai intai root nu mai e parintele lui ala din dreapta
			// dupa aia ala din dreapta are membru stang fosta radacina
			//dupa aia subarborele drept al fostului parinte devine ce avea subaorborele drept in stanga lui
			// subarborele drept devine parintele fostei radacini , adica , radacina

			AVLNode<dataType>* rightSubtree = root->right;
			root->right = rightSubtree->left;
			rightSubtree->left = root;
			root = rightSubtree;
		}
		static void rotateLeft(TreeNode<dataType>*& node, TreeNode<dataType>*& parent) {
			// mai intai root nu mai e parintele lui ala din dreapta
			// dupa aia ala din dreapta are membru stang fosta radacina
			// dupa aia subarborele drept al fostului parinte devine ce avea subaorborele drept in stanga lui
			// subarborele drept devine parintele fostei radacini , adica , radacina

			if (parent) {
				TreeNode<dataType>* rightSubtree = node->right; // store the right side
				node->right = rightSubtree->left;       //the node takes ownership of the right subtrees left 
				rightSubtree->left = node;			    // now the right subtree owns the left
				if (parent->val > node->val)
					parent->left = rightSubtree;			// reassigning the orignal nodes parent
				else
					parent->right = rightSubtree;
			}
			else {
				rotateLeft(node);
			}
		}
		static void rotateRight(TreeNode<dataType>*& root) {
			TreeNode<dataType>* leftSubtree = root->left;
			root->left = leftSubtree->right;
			leftSubtree->right = root;
			root = leftSubtree;
		}
		static void rotateRight(TreeNode<dataType>*& node, TreeNode<dataType>*& parent) {
			if (parent) {
				TreeNode<dataType>* leftSubtree = node->left;
				node->left = leftSubtree->right;
				leftSubtree->right = node;
				if (parent->val > node->val)
					parent->left = leftSubtree;			// reassigning the orignal nodes parent
				else
					parent->right = leftSubtree;
			}
			else {
				rotateRight(node);
			}
		}

		static void detachNode(TreeNode<dataType>*& node, TreeNode<dataType>*& parent) {
			if (node->left && node->right) {
				TreeNode<dataType>* replacement = Utility::inorderSuccessor(node);
				std::swap(node->val, replacement->val);
				node = replacement;
			}
			else if (node->left) {
				parent->left = node->left;
			}
			else if (node->right)
				parent->right = node->right;
		}
	};
}
