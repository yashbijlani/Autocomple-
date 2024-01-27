#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool is_end_of_word;

    TrieNode() : is_end_of_word(false) {}
};

class Trie {
public:
    TrieNode* root;

    Trie() : root(new TrieNode()) {}

    void insert(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (node->children.find(ch) == node->children.end()) {
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
        }
        node->is_end_of_word = true;
    }

    vector<string> wordsFromPrefix(const string& prefix) {
        TrieNode* node = findNode(prefix);
        vector<string> result;
        if (node) {
            getWordsFromNode(node, prefix, result);
        }
        return result;
    }

private:
    TrieNode* findNode(const string& prefix) {
        TrieNode* node = root;
        for (char ch : prefix) {
            if (node->children.find(ch) == node->children.end()) {
                return nullptr;
            }
            node = node->children[ch];
        }
        return node;
    }

    void getWordsFromNode(TrieNode* node, const string& currentPrefix, vector<string>& result) {
        if (node->is_end_of_word) {
            result.push_back(currentPrefix);
            if(result.size()==25)
                return;
        }
        for (const auto& child : node->children) {
            getWordsFromNode(child.second, currentPrefix + child.first, result);
        }
    }
};

int main(int argc, char** argv) {
    Trie trie;

    ifstream wordFile("words_alpha.txt");
    string word;
    while (getline(wordFile, word)) {
        trie.insert(word);
    }
    wordFile.close();

    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <prefix>" << endl;
        return 1;
    }

    string prefixToSearch = argv[1];
    vector<string> resultWords = trie.wordsFromPrefix(prefixToSearch);

    for (int i=0;i<25;i++) {
        cout << resultWords[i] << endl;  
    }

    return 0;
}
