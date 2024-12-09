
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

class TrieNode {
public:
    TrieNode* children[26] = {nullptr};
    vector<int> indexesOfWords;
    bool isEnd = false;
    int indexEnd = numeric_limits<int>::max();
};

class Trie {
private:
    TrieNode* root;

    int charToIndex(char ch) {
        return ch - 'a';
    }

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(const string& word, int indexOfWord) {
        TrieNode* current = root;
        for (char ch : word) {
            int idx = charToIndex(ch);
            if (current->children[idx] == nullptr) {
                current->children[idx] = new TrieNode();
            }
            current = current->children[idx];
            current->indexesOfWords.push_back(indexOfWord);
        }
        current->isEnd = true;
        current->indexEnd = min(current->indexEnd, indexOfWord);
    }

    int searchForWordIndex(const string& query) {
        TrieNode* current = root;
        for (char ch : query) {
            int idx = charToIndex(ch);
            if (current->children[idx] == nullptr) {
                return -1;
            }
            current = current->children[idx];
        }
        return current->isEnd ? current->indexEnd : -1;
    }

    int commonPrefix(const string& query, int currentWordIndex) {
        TrieNode* current = root;
        int actions = 0;

        for (char ch : query) {
            int idx = charToIndex(ch);
            if (current->children[idx] != nullptr) {
                current = current->children[idx];

                if (currentWordIndex == -1) {
                    actions += current->indexesOfWords.size();
                } else {
                    int index = binarySearch(current->indexesOfWords, currentWordIndex + 1);
                    if (index != -1) {
                        actions += index + 1;
                    } else {
                        break;
                    }
                }
            } else {
                break;
            }
        }
        return actions;
    }

private:
    int binarySearch(const vector<int>& list, int target) {
        int left = 0;
        int right = list.size() - 1;
        int resultIndex = -1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (list[mid] < target) {
                resultIndex = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return resultIndex;
    }
};

int main() {
    int n;
    cin >> n;
    cin.ignore();

    Trie trie;

    for (int i = 0; i < n; i++) {
        string word;
        getline(cin, word);
        trie.insert(word, i);
    }

    int q;
    cin >> q;
    cin.ignore();

    for (int i = 0; i < q; i++) {
        string query;
        getline(cin, query);

        int currentWordIndex = trie.searchForWordIndex(query);
        int actionsDuringWordIteration = (currentWordIndex == -1) ? n : currentWordIndex + 1;
        int actionsDuringLettersIteration = 0;

        actionsDuringLettersIteration += trie.commonPrefix(query, currentWordIndex);
        cout << actionsDuringLettersIteration + actionsDuringWordIteration << endl;
    }

    return 0;
}
