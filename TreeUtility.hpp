#pragma once
#include "TreeNode.hpp"
#include <functional>
#include <string>
#include <array>

namespace Tree {
	namespace Utility{
        template <typename T>
        int height(TreeNode<T>* root) {
            if (root == nullptr) return 0;
            return 1 + std::max(height(root->left), height(root->right));
        }
        template <typename T>
        TreeNode<T>* inorderSuccessor(TreeNode<T>* node) {
            node = node->right;
            while (node) {
                node = node->left;
            }
            return node;
        }
        template<typename T>
        void breathFirstIteration(TreeNode<T>* node , std::function<void(TreeNode<T>*)> process) {
            std::queue<TreeNode<T>*> queue;
            queue.push(node);
            while (queue.empty() == false) {
                TreeNode<T>* current = queue.front();
                queue.pop();

                if (current->left)
                    queue.push(current->left);
                if (current->right)
                    queue.push(current->right);

                process(current);
            }
        }
        template <typename T>
        void levelTraversal(TreeNode<T>* root, std::function<void(TreeNode<T>*)> processNode, std::function<void()> onLevelStart) {
            std::array<std::queue<TreeNode<T>*>, 2> alternatingQueues;
            //current queue flag
            bool flag = 0;

            alternatingQueues[flag].emplace(root);

            do {
                onLevelStart();

                while (alternatingQueues[flag].empty() == false) {
                    TreeNode<T>* node = alternatingQueues[flag].front();
                    alternatingQueues[flag].pop();
                    if (node->left) {
                        alternatingQueues[!flag].emplace(node->left);
                    }
                    if (node->right) {
                        alternatingQueues[!flag].emplace(node->right);
                    }
                    processNode(node);
                }

                if (alternatingQueues[!flag].empty()) {
                    break;
                }
                else
                    flag = !flag;

            } while (true);
            
        }

        template <typename T>
        void levelTraversalWithNull(TreeNode<T>* root, std::function<void(TreeNode<T>*)> processNode, std::function<void()> onLevelStart) {
            std::array<std::queue<TreeNode<T>*>, 2> alternatingQueues;
            //current queue flag
            bool flag = 0;

            alternatingQueues[flag].emplace(root);

            do {
                bool hasValidNode = false;
                onLevelStart();

                while (alternatingQueues[flag].empty() == false) {
                    TreeNode<T>* node = alternatingQueues[flag].front();
                    alternatingQueues[flag].pop();

                    if (node) {
                        alternatingQueues[!flag].emplace(node->left);
                        alternatingQueues[!flag].emplace(node->right);
                        hasValidNode = true;
                    }
                    else
                    {
                        alternatingQueues[!flag].emplace(nullptr);
                        alternatingQueues[!flag].emplace(nullptr);
                    }
                    processNode(node);
                }

                if (hasValidNode == false) {
                    break;
                }
                else
                    flag = !flag;

            } while (true);

        }


        
        template<typename T>
        std::vector<int> generateTreeArray(TreeNode<int>* root) {
           
        }
        inline void shut(TreeNode<int>* root) {
            std::vector<std::string> lineList;
            int32_t i = -1;
            std::string spacing = "   ";
            auto processNode = [&lineList , &i , spacing](TreeNode<int>* node) {
                if (node == nullptr) {
                    lineList[i] += "null";
                }
                else {
                    lineList[i] += std::to_string(node->val);
                    lineList[i] += spacing;
                }
            };
            auto onLevelStart = [&lineList , &i]() {
                lineList.emplace_back();
                i++;
            };
            levelTraversalWithNull<int>(root, processNode, onLevelStart);

            
        }

	}
}