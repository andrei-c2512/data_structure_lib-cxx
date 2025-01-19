#pragma once
#include "TreeNode.hpp"


namespace Tree {
	template<typename T>
	class TreeInterface {
	public:
		virtual void insert(const T& val) = 0;
		virtual void erase(const T& val) = 0;
		virtual TreeNode<T>* remove(const T& val) = 0;
	};
	
	template<typename T>
	class SearchTreeInterface : public TreeInterface<T> {
	public:
		virtual TreeNode<T>* search(const T& val) const = 0;
	};
}
