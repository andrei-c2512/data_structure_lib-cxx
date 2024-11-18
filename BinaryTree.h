#pragma once
#include "TreeNode.h"
#include <queue>
#include <vector>
#include <iostream>
#include <stack>

namespace BinaryTree {

    
    template <typename T>
    void show(TreeNode<T>* tree) {

        std::queue<TreeNode<T>*> q;
        q.push(tree);
        while (!q.empty()) {
            TreeNode<T>* node = q.front();
            q.pop();
            int n = node->val;
            std::cout << n << ' ';
            if (node->left)
                q.push(node->left);
            if (node->right)
                q.push(node->right);
        }
        std::cout << std::endl;
    }
    template<typename T>
    void preorderTraversal(TreeNode<T>* tree) {
        std::stack<TreeNode<T>*> stack;

        stack.push(tree);
        while (stack.empty() == false) {
            TreeNode<T>* node = stack.top();
            stack.pop();
            if (node->right)
                stack.push(node->right);

            if (node->left)
                stack.push(node->left);

            std::cout << node->val << ' ';
        }
    }
    template<typename T>
    void inorderTraversal(TreeNode<T>* tree) {
        if (tree->left)
            inorderTraversal(tree->left);

        std::cout << tree->val << ' ';

        if (tree->right)
            inorderTraversal(tree->right);
    }
    template<typename T>
    void postorderTraversal(TreeNode<T>* tree) {
        if (tree->left)
            postorderTraversal(tree->left);
        if (tree->right)
            postorderTraversal(tree->right);

        std::cout << tree->val << ' ';
    }
    //bfs
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
    std::vector<float> bfsAveragePerLevel(TreeNode<T>* root) {
        std::vector<float> vec;

        std::queue<TreeNode<T>*> q;
        std::queue<TreeNode<T>*> next;
        q.emplace(root);

        float avg = 0.0f;
        int32_t n = 1;
        int32_t i = 0;
        do {
            while (q.empty()== false) {
                TreeNode<T>* node = q.front();
                q.pop();

                avg += node->val;

                if (node->left)
                    next.push(node->left);
                if (node->right)
                    next.push(node->right);
            }
            vec.emplace_back(
                avg / float(q.size()
            );
            avg = 0.0f;
        } while (next.empty() == false);

        return vec;
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
            for (; i < cap && i < vec.size(); i++) {
                //verifica daca i-ul e pe pozitie para pe acel nivel
                if (!((i - (cap - n)) & 1)) {
                    current = queue.front();
                    queue.pop();
                }
                if (vec[i] != exclude)
                    queue.push(
                        current->add(!(i & 1), vec[i])
                    );

            }
            //cresc nivelul
            n *= 2;
            cap += n;
        }
        return root;
    }
    template<typename T>
    void insert(TreeNode<T>* parent, const T& info, bool dir) {
        parent->add(dir, info);
    }

    template<typename T>
    TreeNode<T>* merge(TreeNode<T>* tree1, TreeNode<T>* tree2) {
        TreeNode<T>* tree3 = new TreeNode<T>(0);

        std::queue<TreeNode<T>*> q1;
        std::queue<TreeNode<T>*> q2;

        std::vector<T> vec;
        q1.push(tree1);
        q2.push(tree2);

        while (!(q1.empty() && q2.empty())) {
            TreeNode<T>* current1 = (!q1.empty()) ? q1.front() : nullptr;
            TreeNode<T>* current2 = (!q2.empty()) ? q2.front() : nullptr;

            if (current1) {
                q1.push(current1->left);
                q1.push(current1->right);
            }
            if (current2) {
                q2.push(current2->left);
                q2.push(current2->right);
            }

            
            T val = ((current1) ? current1->val : 0) +
                ((current2) ? current2->val : 0);

            vec.emplace_back(val);
            if(!q1.empty()) q1.pop();
            if(!q2.empty()) q2.pop();
        }
        for (const T& c : vec)
            std::cout << c << ' ';
        std::cout << std::endl;
        return create(vec , T{});
    }
}
