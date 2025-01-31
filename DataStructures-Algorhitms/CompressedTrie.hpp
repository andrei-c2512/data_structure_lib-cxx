#pragma once
#include <string>
#include "TreeUtility.hpp"
#include "TrieInterface.hpp"
#include <stack>

namespace Tree {
	struct CTrieNode {
		CTrieNode() {
			str = '\0';
			wordEnd = false;
			Utility::setArrToNull(list, 'z' - 'a');
		}
		CTrieNode(const std::string& str0, bool wordEnd0 = false) {
			str = str0;
			wordEnd = wordEnd0;
			Utility::setArrToNull(list, 'z' - 'a');
		}
		~CTrieNode() {
			Utility::cleanUpArray(list, 'z' - 'a');
		}
		bool hasChildren() const noexcept {
			return !Utility::nullArray<CTrieNode*>(list, 'z' - 'a');
		}

		std::string str;
		bool wordEnd = false;
		CTrieNode* list['z' - 'a'];
	};
	//this should be used for static lookup
	class CompressedTrie : public TrieInterface{
	public:
		CompressedTrie() {
			root = new CTrieNode;
		}
		CompressedTrie(const CompressedTrie& t) = delete;
		CompressedTrie operator=(const CompressedTrie& t) = delete;
		CompressedTrie(CompressedTrie&& t) {
			root = t.root;
			t.root = nullptr;
		}
		CompressedTrie& operator=(CompressedTrie&& t) {
			root = t.root;
			t.root = nullptr;
			return *this;
		}
		~CompressedTrie() {
			if(root)
				delete root;
		}

		void addWord(const char* word) {
			CTrieNode* last = nullptr;
			CTrieNode* current = root;
			size_t len = std::strlen(word);

			for (size_t i = 0; i < std::strlen(word); i++) {
				last = current;
				current = current->list[word[i] - 'a'];

				if (current == nullptr) {
					last->list[word[i] - 'a'] = new CTrieNode(word[i]);
					current = last->list[word[i] - 'a'];
				}
			}
			current->wordEnd = true;
		}
		bool wordExists(const char* word) const override {
			CTrieNode* node = traversePath(word);
			//return if we are at the end of the word and if the current node repesents a word end
			return node && node->wordEnd;
		}
		void eraseWord(const char* word) override {
			//I will delete them from end to start
			std::stack<CTrieNode*> stack;

			CTrieNode* current = root;
			stack.emplace(current);


			size_t i = 0;
			for (; i < std::strlen(word); i++) {
				current = current->list[word[i] - 'a'];
				stack.emplace(current);

				//the word doesn't even exist , so just exit
				if (current == nullptr)
					return;
			}

			//the first pop
			current = stack.top();
			stack.pop();
			CTrieNode* last = stack.top();

			if (!current->hasChildren()) {
				delete current;
				current = last;
			}
			else if (current->wordEnd) {
				current->wordEnd = false;
				// no point in continuing if any of the word's character nodes has children , 
				// since we can't delete them. Otherwise we mess up the tree
				return;
			}

			while (stack.empty() == false) {
				CTrieNode* last = stack.top();

				if (!current->hasChildren()) {
					delete current;
					current = last;
				}
				else
					return;
			}
		}
		void removeWord(const char* word) override {
			CTrieNode* node = traversePath(word);

			if (node->wordEnd)
				node->wordEnd = false;
		}
		std::vector<std::string> wordsWithPrefix(const char* prefix) {
			CTrieNode* node = traversePath(prefix);
			if (node == nullptr)
				return {};

			std::vector<std::string> wordList;

			std::stack<std::string> wordStack;
			wordStack.emplace(std::string(prefix));
			std::stack<CTrieNode*> nodeStack;
			nodeStack.emplace(node);

			while (nodeStack.empty() == false) {
				CTrieNode* current = nodeStack.top();
				nodeStack.pop();

				std::string str = wordStack.top();
				wordStack.pop();

				if (current->wordEnd && current->hasChildren() == false) {
					wordList.emplace_back(str);
					continue;
				}

				for (CTrieNode* n : current->list) {
					if (n != nullptr) {
						nodeStack.emplace(n);
						wordStack.emplace(str + n->str);
					}
				}
			}

			return wordList;
		}
	private:
		CTrieNode* traversePath(const char* word) const noexcept {
			size_t i = 0;
			CTrieNode* current = root;
			for (; i < std::strlen(word); ) {
				current = current->list[word[i] - 'a'];

				//words with such prefix don't exist , so return
				if (current == nullptr)
					return nullptr;
				else
					i += current->str.size();
			}
			return current;
		}
	private:
		CTrieNode* root;
	};
}
