#pragma once
#include "TreeNode.hpp"

namespace TinyDS::Tree {
	namespace Utility{
        template <typename T , typename Tag>
        int height(TreeNode<T , Tag>* root) {
            if (root == nullptr) return 0;
            return 1 + std::max(height(root->left), height(root->right));
        }
        template <typename T>
        T* inorderSuccessor(T* node) {
            node = node->right;
            while (node) {
                node = node->left;
            }
            return node;
        }
        template<typename T, typename Tag>
        void breathFirstIteration(TreeNode<T, Tag>* node , std::function<void(TreeNode<T, Tag>*)> process) {
            std::queue<TreeNode<T, Tag>*> queue;
            queue.push(node);
            while (queue.empty() == false) {
                TreeNode<T, Tag>* current = queue.front();
                queue.pop();

                if (current->left)
                    queue.push(current->left);
                if (current->right)
                    queue.push(current->right);

                process(current);
            }
        }
        template <typename T, typename Tag>
        void levelTraversal(TreeNode<T, Tag>* root, std::function<void(TreeNode<T, Tag>*)> processNode, std::function<void()> onLevelStart) {
            std::array<std::queue<TreeNode<T , Tag>*>, 2> alternatingQueues;
            //current queue flag
            bool flag = 0;

            alternatingQueues[flag].emplace(root);

            do {
                onLevelStart();

                while (alternatingQueues[flag].empty() == false) {
                    TreeNode<T , Tag>* node = alternatingQueues[flag].front();
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

        template <typename T, typename Tag>
        void levelTraversalWithNull(TreeNode<T, Tag>* root, std::function<void(TreeNode<T , Tag>*)> processNode, std::function<void()> onLevelStart) {
            std::array<std::queue<TreeNode<T , Tag>*>, 2> alternatingQueues;
            //current queue flag
            bool flag = 0;

            alternatingQueues[flag].emplace(root);

            do {
                bool hasValidNode = false;
                onLevelStart();

                while (alternatingQueues[flag].empty() == false) {
                    TreeNode<T , Tag>* node = alternatingQueues[flag].front();
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


        
        /*template<typename Tag >
        std::vector<int> generateTreeArray(TreeNode<int , Tag>* root) {
           
        }*/
        template<typename Tag >
        inline void shut(TreeNode<int ,Tag>* root) {
            std::vector<std::string> lineList;
            int32_t i = -1;
            std::string spacing = "   ";
            auto processNode = [&lineList , &i , spacing](TreeNode<int, Tag>* node) {
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

        template<typename T>
        bool nullArray(const T* array, size_t size) {
            for (size_t i = 0; i < size; i++) {
                if (array[i] != nullptr)
                    return false;
            }
            return true;
        }

        template<typename T>
        void setArrToNull(T* array, size_t size) {
            for (size_t i = 0; i < size; i++) {
                array[i] = nullptr;
            }
        }

        template<typename T>
        void cleanUpArray(T* array, size_t size) {
            for (size_t i = 0; i < size; i++) {
                if (array[i] != nullptr) {
                    delete array[i];
                }
            }
        }

        size_t BSTStartCoeficient(size_t treeHeight, size_t level) {
            if (level >= treeHeight - 1)
                return 0;

            size_t sum = 1;
            for (size_t i = 1; i < treeHeight - level - 1; i++)
                sum += (size_t)pow(2, i);

            return sum;
        }
        size_t BSTSSpacingCoeficient(size_t treeHeight, size_t level) {

            size_t sum = 1;
            for (size_t i = 1; i < treeHeight - level; i++)
                sum += (size_t)pow(2, i);

            return sum;
        }

        template<typename T>
        static void rotateLeft(T*& root) {
            //mai intai root nu mai e parintele lui ala din dreapta
            // dupa aia ala din dreapta are membru stang fosta radacina
            //dupa aia subarborele drept al fostului parinte devine ce avea subaorborele drept in stanga lui
            // subarborele drept devine parintele fostei radacini , adica , radacina

            T* rightSubtree = root->right;
            root->right = rightSubtree->left;
            rightSubtree->left = root;
            root = rightSubtree;
        }

        template <typename T>
        static void rotateLeft(T*& node, T*& parent) {
            // mai intai root nu mai e parintele lui ala din dreapta
            // dupa aia ala din dreapta are membru stang fosta radacina
            // dupa aia subarborele drept al fostului parinte devine ce avea subaorborele drept in stanga lui
            // subarborele drept devine parintele fostei radacini , adica , radacina

            if (parent) {
                T* rightSubtree = node->right; // store the right side
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
        template<typename T>
        static void rotateRight(T*& root) {
            T* leftSubtree = root->left;
            root->left = leftSubtree->right;
            leftSubtree->right = root;
            root = leftSubtree;
        }
        template<typename T>
        static void rotateRight(T*& node, T*& parent) {
            if (parent) {
                T* leftSubtree = node->left;
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
        template<typename T>
        static void detachNode(T*& node, T*& parent) {
            if (node->left && node->right) {
                T* replacement = Utility::inorderSuccessor(node);
                std::swap(node->val, replacement->val);
                node = replacement;
            }
            else if (node->left) {
                parent->left = node->left;
            }
            else if (node->right)
                parent->right = node->right;
        }
	}
}
