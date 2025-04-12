#include "Trie.hpp"   

namespace TinyDS::Tree{
    TrieNode::TrieNode() {
            ch = '\0';
            wordEnd = false;
            Utility::setArrToNull(list, 'z' - 'a');
    }
    TrieNode::TrieNode(char ch0, bool wordEnd0 ) {
            ch = ch0;
            wordEnd = wordEnd0;
            Utility::setArrToNull(list, 'z' - 'a');
    }
    TrieNode::~TrieNode() {
            Utility::cleanUpArray(list, 'z' - 'a');
    }
    bool TrieNode::hasChildren() const noexcept {
            return !Utility::nullArray<TrieNode*>(list, 'z' - 'a');
    }

    std::optional<TrieNode*> TrieNode::hasOneChild() const {
            size_t cnt = 0;
            for (size_t i = 0; i < 'z' - 'a'; i++) {
                    //if()
            }
            return std::nullopt;
    }
    Trie::Trie() {
        root = new TrieNode;
    }
    Trie::Trie(std::vector<const char*> list) {
            root = new TrieNode;
            for (size_t i = 0; i < list.size(); i++) {
                    addWord(list[i]);
            }
    }
    Trie& Trie::operator=(Trie&& t) {
            root = t.root;
            t.root = nullptr;
            return *this;
    }
    Trie::Trie(Trie&& t) {
            root = t.root;
            t.root = nullptr;
    }
    Trie::~Trie() {
            if(root != nullptr)
                    delete root;
    }
    void Trie::addWord(const char* word) {
            TrieNode* last = nullptr;
            TrieNode* current = root;

            for (size_t i = 0; i < std::strlen(word); i++) {
                    last = current;
                    current = current->list[word[i] - 'a'];

                    if (current == nullptr) {
                            last->list[word[i] - 'a'] = new TrieNode(word[i]);
                            current = last->list[word[i] - 'a'];
                    }
            }
            current->wordEnd = true;
    }
    bool Trie::wordExists(const char* word) const {
            TrieNode* node = traversePath(word);
            //return if we are at the end of the word and if the current node repesents a word end
            return node && node->wordEnd;
    }
    void Trie::eraseWord(const char* word) {
            //I will delete them from end to start
            std::stack<TrieNode*> stack;

            TrieNode* current = root;
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
            TrieNode* last = stack.top();

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
                    TrieNode* last = stack.top();

                    if (!current->hasChildren()) {
                            delete current;
                            current = last;
                    }
                    else
                            return;
            }
    }
    void Trie::removeWord(const char* word) {
            TrieNode* node = traversePath(word);

            if (node->wordEnd)
                    node->wordEnd = false;
    }
    std::vector<std::string> Trie::wordsWithPrefix(const char* prefix) {
            TrieNode* node = traversePath(prefix);
            if (node == nullptr)
                    return {};

            std::vector<std::string> wordList;

            std::stack<std::string> wordStack;
            wordStack.emplace(std::string(prefix));
            std::stack<TrieNode*> nodeStack;
            nodeStack.emplace(node);

            while (nodeStack.empty() == false) {
                    TrieNode* current = nodeStack.top();
                    nodeStack.pop();

                    std::string str = wordStack.top();
                    wordStack.pop();

                    if (current->wordEnd && current->hasChildren() == false) {
                            wordList.emplace_back(str);
                            continue;
                    }

                    for (TrieNode* n : current->list) {
                            if (n != nullptr) {
                                    nodeStack.emplace(n);
                                    wordStack.emplace(str + n->ch);
                            }
                    }
            }

            return wordList;
    }
    bool Trie::isNull() const{
            return root->hasChildren() == false;
    }
    TrieNode* Trie::traversePath(const char* word) const noexcept {
            size_t i = 0;
            TrieNode* current = root;
            for (; i < std::strlen(word); i++) {
                    current = current->list[word[i] - 'a'];

                    //words with such prefix don't exist , so return
                    if (current == nullptr)
                            return nullptr;
            }
            return current;
    }

}

