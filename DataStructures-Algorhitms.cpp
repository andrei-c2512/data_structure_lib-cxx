// DataStructures-Algorhitms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "BinaryTree.h"

using namespace std;
int main()
{
    /*std::vector<char> vec = {'C' , 'E' , 'G' , 'K' , 'A' , 'M' , 'D' , '0' , 'B' , 'L' , 'F' , '0'  , '0' , 'I' , '0'};
    TreeNode<char>* root = BinaryTree::create(vec , '0');

    BinaryTree::preorderTraversal(root);
    cout << endl;*/
    std::vector<int> v1 = { 1 , 3 , 2 , 5 , 0 , 0 , 0};
    std::vector<int> v2 = { 2 , 1 , 3 , 0 , 4, 0 , 7};

    TreeNode<int>* tree1 = BinaryTree::create(v1, 0);
    TreeNode<int>* tree2 = BinaryTree::create(v2, 0);

    BinaryTree::show<int>(tree1);
    BinaryTree::show<int>(tree2);

    TreeNode<int>* tree3 = BinaryTree::merge(tree1, tree2);
    BinaryTree::show<int>(tree3);
    cout << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
