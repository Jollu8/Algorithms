#include <algorithm>
#include <fstream>
#include <iostream>
#include <string_view>
#include <string>
#include <memory>
#include <vector>
#include <utility>
#include <numeric>
#include <limits>


class Autocomplete {
    struct trie {
        std::vector<trie *> ch;
        int index;
        int top;
        trie() : index(-1), top(-1), ch(26, nullptr) {}
    };

public:
    explicit Autocomplete(std::ifstream &in) : N(0), Q(0), root(new trie()) {
        reader(in);
    }

    void solve(std::ofstream &out) {
        for (auto i: m_ans) out << i << '\n';
    }

private:
    void reader(std::ifstream &in) {
        in >> N >> Q;
        std::string top, query, T, w;
        in.ignore();
        for (int i = 0; i < N; ++i) {
            std::getline(in, w, ' ');
            std::getline(in, top);
            insert(w, std::stoi(top), i + 1);
        }

        for (auto i = 0; i < Q; ++i) {
            std::getline(in, query);
            if (query[0] == '+') T += query[2];
            else if (!T.empty()) T.pop_back();
            m_ans.emplace_back(complete(T));
        }
    }

    void insert(const std::string &w, int top, int i) {
        auto tmp = root;
        if (top > tmp->top) tmp->top = top, tmp->index = i;

        for (auto ch: w) {
            int c = ch - 'a';
            if (!tmp->ch[c]) tmp->ch[c] = new trie();
            tmp = tmp->ch[c];
            if (tmp->top < top)tmp->top = top, tmp->index = i;
        }
    }

    int complete(const std::string &pref) {
        auto tmp = root;
        for (auto c: pref) {
            int i = c - 'a';
            if (!tmp->ch[i])return -1;
            tmp = tmp->ch[i];
        }
        return tmp->index;
    }

private: // Fields
    int N, Q;
    std::vector<int> m_ans;
    trie *root;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::ifstream file_name("input.txt");
    Autocomplete f(file_name);
    std::ofstream out("output.txt");
    f.solve(out);
}

