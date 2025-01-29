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
	template<std::totally_ordered dataType , TreeTypeAdapter<dataType> adapter = dataType, typename Tag = NoTag>
	class TreeInterface {
	public:
		virtual ~TreeInterface() = default;
		virtual void insert(const adapter& val) = 0;
		virtual void erase(const adapter& val) = 0;
		[[nodiscard]] virtual TreeNode<dataType , Tag>* remove(const adapter& val) = 0;
	};
	
	template<typename dataType ,  typename adapter = dataType , typename Tag = NoTag>
	class AbstractSearchTree : public TreeInterface<dataType , adapter , Tag> {
	public:
		virtual ~AbstractSearchTree() = default;
		virtual TreeNode<dataType , Tag>* search(const adapter& val) const = 0;
	
	};
}
