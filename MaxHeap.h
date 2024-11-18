#pragma once
#include "TreeNode.h"
#include <queue>
#include <stack>

template<typename T>
class MaxHeap {
public:
    MaxHeap() = default;
    MaxHeap(const std::vector<T>& vec, T exclude) {
        if (!vec.size()) return;
        int n = 2;

        std::queue<TreeNode<T>*> queue;
        root = new TreeNode<T>(vec[0]);
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
    }
    void eraseRoot() {
        T last = eraseLast();
        root->val = last;
        maxHeap(root);
    }
    //applies max heap property from given node downwards
    void maxHeap(TreeNode<T>* heap) {
        TreeNode<T>* current = heap;
        TreeNode<T>* next = nullptr;

        auto verify = [current, next]() {
            if (next && next->val > current->val) {
                std::swap(next->val, current->val);
                current = next;
            }
        }


        do {
            next = current->left;
            verify();
            else {
                next = current->right;
                verify();
            }
        } while (next != nullptr);
    }
private:
    TreeNode<T>* back() {
        TreeNode<T>* last = nullptr;
        std::queue<TreeNode<T>*> currentLayer;
        std::queue<TreeNode<T>*> nextLayer;

        currentLayer.push(root);
        do{

            while (currentLayer.empty() == false)
            {
                TreeNode<T>* n = currentLayer.front();
                if (n->left)
                    nextLayer.push(n->left);
                if (n->right)
                    nextLayer.push(n->right);
                last = n;
                currentLayer.pop();
            }
            currentLayer = nextLayer;
            nextLayer.clear();
        } while (!currentLayer.empty());
        
        return last;
    }
    T eraseLast() {
        TreeNode<T>* last = nullptr;
        TreeNode<T>* lastParent = nullptr;

        std::queue<TreeNode<T>*> q;

        q.push(root);
        
        while (q.empty() == false) {
            TreeNode<T>* node = q.front();
            q.pop();

            if (node->left)
                q.push(node->left);
            if (node->right)
                q.push(node->right);

            lastParent = last;
            last = node;
        }

        if (lastParent->right)
            lastParent->right = nullptr;
        else
            lastParent->left = nullptr;

        T val = last->val;
        delete last;

        return val;
    }
private:
    TreeNode<T>* root = nullptr;
};