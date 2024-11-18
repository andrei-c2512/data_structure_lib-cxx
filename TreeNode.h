#pragma once
#include <iostream>
#include <queue>

template<typename T>
struct TreeNode {
    TreeNode() = default;
    TreeNode(int val0) : val(val0) {}
    
    TreeNode* add(bool onRight, T val) {
        if (onRight)
        {
            right = new TreeNode<T>(val);
            return right;
        }
        else
        {
            left = new TreeNode<T>(val);
            return left;
        }
    }
    //this function assumes that the node is a edge node
    void remove(TreeNode* node) {
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
    TreeNode<T>* left = nullptr;
    TreeNode<T>* right = nullptr;
};

template <typename T>
void show(TreeNode<T>* tree) {
    std::cout << tree->val << ' ';
    if (tree->left)
        show(tree->left);
    if (tree->right)
        show(tree->right);
}

template <typename T>
void breathFirstSearch(TreeNode<T>* tree) {
    if (tree == nullptr) return;

    std::queue<TreeNode<T>*> queue;
    std::queue<TreeNode<T>*> nextLayer;
    queue.push(tree);

    do {
        while (!queue.empty()) {
            TreeNode<T>* n = queue.front();
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
template <typename T>
TreeNode<T>* create(std::vector<T> vec, T exclude) {
    if (!vec.size()) return nullptr;
    int n = 2;

    std::queue<TreeNode<T>*> queue;
    TreeNode<T>* root = new TreeNode<T>(vec[0]);
    queue.push(root);
    int i = 1;
    int cap = n + n / 2;
    while (i < vec.size()) {
        TreeNode<T>* current = nullptr;
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