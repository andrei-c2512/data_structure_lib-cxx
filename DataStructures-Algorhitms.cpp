// DataStructures-Algorhitms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
//#include "BinaryTree.h"
#include "RedBlackTree.hpp"
#include "ConsoleRenderer.hpp"
#include "DrawableNode.hpp"
#include "AVLTree.hpp"
#include "Heap.hpp"
#include "SortingAlghoritms.hpp"
#include "Trie.hpp"
#include "IntDatasetGenerator.hpp"

using namespace std;

template <typename T>
void print(const std::vector<T>& list) {
    for (const auto& elem : list) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}

class A{};
class B : public A {};\

void func(A*& ptr) {
    if (ptr)
        delete ptr;
    std::cout << "After casting" << '\n';
    ptr = new B;
    std::cout << "After new value" << '\n';
}

int main()
{
    B* b = new B;

    std::cout <<  "Initially: " << b << '\n';
    func(reinterpret_cast<A*&>(b));


    delete b;



    ConsoleRenderer renderer;
    //renderer.draw(DrawableNode<int>(32).drawable);


    Tree::AVLTree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);
    tree.insert(8);
    tree.insert(9);
    tree.insert(10);


    std::cout << sizeof(std::string) << '\n';
    //std::cout << sizeof(Tree::TreeNode<std::string , AVLTag>) << '\n';

    renderer.draw(tree.root);

    renderer.render();

    /*Heap<int> heap;
    heap.setList({ 10 , 5, 13 , 67 , 20 , 1920 , 345 , 11111 });
    heap.sort();
    heap.print();

    std::vector<int> list = { 10 , 5, 13 , 67 , 20 , 1920 , 345 , 11111 };
    print(list);
    auto cmp = [](int lhs, int rhs) {
        return lhs < rhs;
    };
    //Algorhitms::insertionSort(list, cmp);
    //Algorhitms::selectionSort(list, cmp);
    Algorhitms::quickSort(list, cmp);
    print(list);
    */

    //std::vector<const char*> wordList = { "sigma" , "si" , "slgmadan" , "sigjson" , "sigmajohnson" , "sigmafloppa" };
    //Tree::Trie trie(wordList);
    //print(trie.wordsWithPrefix("sigma"));
    
    //IntDatasetGenerator gen;
    //print(gen.generate(10, 1, 100));


    /*std::vector<char> vec = {'C' , 'E' , 'G' , 'K' , 'A' , 'M' , 'D' , '0' , 'B' , 'L' , 'F' , '0'  , '0' , 'I' , '0'};
    TreeNode<char>* root = BinaryTree::create(vec , '0');

    BinaryTree::preorderTraversal(root);
    cout << endl;*/
    /*std::vector<int> v1 = {1 , 3 , 2 , 5 , 0 , 0 , 0};
    std::vector<int> v2 = { 2 , 1 , 3 , 0 , 4, 0 , 7};

    TreeNode<int>* tree1 = BinaryTree::create(v1, 0);
    TreeNode<int>* tree2 = BinaryTree::create(v2, 0);

    BinaryTree::show<int>(tree1);
    BinaryTree::show<int>(tree2);

    TreeNode<int>* tree3 = BinaryTree::merge(tree1, tree2);
    BinaryTree::show<int>(tree3);
    cout << endl;*/
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
