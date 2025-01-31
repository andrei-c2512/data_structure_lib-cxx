#pragma once
#include "TreeNode.hpp"
#include "TreeUtility.hpp"
#include <concepts>
#include "AllocatorInterface.hpp"
#include "BaseAllocator.hpp"


template<typename T , typename A> 
concept TreeTypeAdapter = std::totally_ordered<T> && std::totally_ordered<A> && requires(T lhs, A rhs) {
	{ lhs < rhs } -> std::convertible_to<bool>;
	{ lhs > rhs } -> std::convertible_to<bool>;
	{ lhs == rhs } -> std::convertible_to<bool>;
};

namespace Tree {
	template<std::totally_ordered dataType , typename Tag = NoTag ,
		TreeTypeAdapter<dataType> adapter = dataType>
	class TreeInterface{
	public:
		TreeInterface(){
			allocator = new BaseAllocator(sizeof(TreeNode<dataType, Tag>));
		}
		TreeInterface(AllocatorInterface* allocator0)
		{
			allocator = allocator0;
		}
		virtual ~TreeInterface() {
			delete allocator;
		}
		
		const AllocatorInterface* getAllocator() const noexcept {
			return allocator;
		}
		virtual void insert(const adapter& val) = 0;
		virtual void erase(const adapter& val) = 0;
		[[nodiscard]] virtual TreeNode<dataType , Tag>* remove(const adapter& val) = 0;
	protected:
		AllocatorInterface* allocator;
	};
	
#define INHERIT_ALLOCATOR_METHODS(Class)\
	using Class::allocator;				\
	using Class::getAllocator;


	template<typename dataType ,  typename Tag = NoTag, typename adapter = dataType>
	class AbstractSearchTree : public TreeInterface<dataType ,Tag, adapter> {
	public:
		AbstractSearchTree() = default;
		AbstractSearchTree(AllocatorInterface* allocator)
			:TreeInterface<dataType, Tag , adapter>(allocator)
		{}
		virtual ~AbstractSearchTree() = default;
		virtual TreeNode<dataType , Tag>* search(const adapter& val) const = 0;
	};
}
