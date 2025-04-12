#pragma once
#include <string>
#include "TreeUtility.hpp"
#include "TrieInterface.hpp"
#include <stack>

namespace TinyDS::Tree {
	struct CTrieNode {
		CTrieNode();
		CTrieNode(const std::string& str0, bool wordEnd0 = false);
		~CTrieNode();
		bool hasChildren() const noexcept;
		std::string str;
		bool wordEnd = false;
		CTrieNode* list['z' - 'a'];
	};
	//this should be used for static lookup
	class CompressedTrie : public TrieInterface{
	public:
		CompressedTrie();
		CompressedTrie(const CompressedTrie& t) = delete;
		CompressedTrie operator=(const CompressedTrie& t) = delete;
		CompressedTrie(CompressedTrie&& t);
		CompressedTrie& operator=(CompressedTrie&& t);
		~CompressedTrie();

		void addWord(const char* word);
		bool wordExists(const char* word) const override;
		void eraseWord(const char* word) override;
		void removeWord(const char* word) override;
		std::vector<std::string> wordsWithPrefix(const char* prefix);
	private:
		CTrieNode* traversePath(const char* word) const noexcept;
	private:
		CTrieNode* root;
	};
}
