#pragma once
#include "AVLTree.hpp"
#include "PoolAllocator.hpp"
#include <map>
#include <memory>
#include "Clock.hpp"
#include "PoolAllocator.hpp"

namespace Testing {
	void performanceTest() {
		Tree::AVLTree<int> defaultTree;
		PoolAllocator* allocator = new PoolAllocator(sizeof(Tree::TreeNode<int, Tree::AVLTag>));
		allocator->reserve(10001);
		Tree::AVLTree<int> poolTree(allocator);
		Tree::AVLTree<int> testTree;
		std::map<int, int> map;
		std::map<int, int> map2;


		int cap = 1000;
		for (int i = 0; i < cap; i++) {
			defaultTree.insert(i);
			poolTree.insert(i);
			testTree.insert(i);
			map.emplace(i, i);
			map2.emplace(i, i);
		}
		//I believe the compiler does some optimisations because I do the same searches every time , since the first time is usually
		//the SLOWEST

		Clock clock;
		clock.start();
		for (auto i = 0; i < cap; i++) {
			testTree.search(i);
		}
		clock.bench("Nigga");

		clock.start();
		for (auto i = 0; i < cap; i++) {
			poolTree.search(i);
		}
		clock.bench("Tree with pool allocator");

		clock.start();
		for (auto i = 0; i < cap; i++) {
			defaultTree.search(i);
		}
		clock.bench("Default implementation(no custom allocator)");

		clock.start();
		for (auto i = 0; i < cap; i++) {
			map[i];
		}
		clock.bench("Standard implementation 1");

		clock.start();
		for (auto i = 0; i < cap; i++) {
			map2[i];
		}
		clock.bench("Standard implementation 2");

		//conclusion: a pool allocator makes a small difference in performance , and in fact , adding noexcept to the 
		//search function made a bigger difference lol
	}
}