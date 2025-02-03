#pragma once
#include <iostream>
#include "Common.hpp"
#include "MemoryUtility.hpp"

namespace Tree {
    template<typename T , typename Tag>
    struct TreeNode : public Tag{
        TreeNode() = default;
        TreeNode(const T& val0) 
            : val(val0) {}

        TreeNode<T , Tag>* add(bool onRight, T val) {
            if (onRight)
            {
                right = new TreeNode<T , Tag>(val);
                return right;
            }
            else
            {
                left = new TreeNode<T ,  Tag>(val);
                return left;
            }
        }
        //this function assumes that the node is a edge node
        void remove(TreeNode<T , Tag>* node) {
            if (node == left)
            {
                delete left;
                left = node = nullptr;
            }
            else if (node == right) {
                delete right;
                left = node = nullptr;
            }
            else
                std::cout << "Invalid node";
        }


        T val{};
        TreeNode<T, Tag>* left = nullptr;
        TreeNode<T, Tag>* right = nullptr;
        char padding[MemoryUtility::calculatePadding(2 * sizeof(TreeNode<T , Tag>*) + sizeof(T))];
    };

    enum class NodeColor : int8_t {
        RED = 0x0, BLACK = 0x1
    };


    struct NoTag {};
    struct AVLTag {
        int8_t balanceFactor = 0;
    };
    struct RedBlackTag {
        NodeColor color;
    };


    template <typename DataType , typename Tag>
    void show(TreeNode<DataType, Tag>* tree) {
        std::cout << tree->val << ' ';
        if (tree->left)
            show(tree->left);
        if (tree->right)
            show(tree->right);
    }

    template <typename DataType, typename Tag>
    void breathFirstSearch(TreeNode<DataType, Tag>* tree) {
        if (tree == nullptr) return;

        std::queue<TreeNode<DataType, Tag>*> queue;
        std::queue<TreeNode<DataType, Tag>*> nextLayer;
        queue.push(tree);

        do {
            while (!queue.empty()) {
                TreeNode<DataType, Tag>* n = queue.front();
                if (n->left)
                    nextLayer.push(n->left);
                if (n->right)
                    nextLayer.push(n->right);

                std::cout << n->val;
                queue.pop();
            }
            queue = nextLayer;
        } while (!queue.empty());
    }
    template <typename DataType, typename Tag>
    TreeNode<DataType, Tag>* create(std::vector<DataType> vec, DataType exclude) {
        if (!vec.size()) return nullptr;
        int n = 2;

        std::queue<TreeNode<DataType , Tag>*> queue;
        TreeNode<DataType, Tag>* root = new TreeNode<DataType, Tag>(vec[0]);
        queue.push(root);
        int i = 1;
        int cap = n + n / 2;
        while (i < vec.size()) {
            TreeNode<DataType, Tag>* current = nullptr;
            for (; i < cap; i++) {
                if (!((i - (cap - n)) & 1)) {
                    current = queue.front();
                    queue.pop();
                }
                if (vec[i] != exclude)
                    queue.push(
                        current->add(!(i & 1), vec[i])
                    );

            }
            n *= 2;
            cap += n;
        }
        return root;
    }

}
