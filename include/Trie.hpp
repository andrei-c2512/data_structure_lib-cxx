#pragma once
#include "TreeUtility.hpp"
#include "TrieInterface.hpp"



namespace TinyDS{
    namespace Tree {	
        struct TrieNode {
                TrieNode();
                TrieNode(char ch0, bool wordEnd0 = false);
                ~TrieNode(); bool hasChildren() const noexcept;
                std::optional<TrieNode*> hasOneChild() const; 
                char ch; 
                bool wordEnd = false; 
                TrieNode* list['z' - 'a'];
        };


	class Trie : public TrieInterface {
	public:
		Trie();
		Trie(std::vector<const char*> list);
		Trie& operator=(const Trie& t) = delete;
		Trie(const Trie& t) = delete;
		Trie& operator=(Trie&& t);
		Trie(Trie&& t);
		~Trie();
		void addWord(const char* word);
		bool wordExists(const char* word) const override;
		void eraseWord(const char* word) override;
		void removeWord(const char* word) override;
		std::vector<std::string> wordsWithPrefix(const char* prefix);
		bool isNull() const override;
	private:
		TrieNode* traversePath(const char* word) const noexcept;
	private:
		TrieNode* root;
	};
    }
}
