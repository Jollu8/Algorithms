#pragma GCC optimize("O3")

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


using namespace std;

class Automatic {
    int N{}, Q{};
    std::vector<string> m_dictionary;
    vector<int> m_ans;

public:
    explicit Automatic(ifstream &in) {
        in >> N >> Q;
        m_dictionary = vector<string>(N);
        m_ans = vector<int>(Q);
        reader(in);
    }

    void solve(ofstream &out) {
        for (auto &i: m_ans) out << i << '\n';
    }

    void reader(ifstream &in) {
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        for (int i = 0; i < N; ++i) std::getline(in, m_dictionary[i]);
        std::string pref;
        for (int i = 0, k = 0; i < Q; ++i) {
            in >> k >> pref;
            m_ans[i] = find_word(pref, k);
        }
    }

    int find_word(string &pref, int k) {
        int l{}, r = m_dictionary.size() - 1;

        while (l <= r) {
            int m = l + (r - l) / 2;
            if (m_dictionary[m].substr(0, pref.size()) == pref) {
                if (!m || m_dictionary[m - 1].substr(0, pref.size()) != pref) {
                    l = m;
                    break;
                } else r = m - 1;
            } else if (m_dictionary[m] < pref) l = m + 1;
            else r = m - 1;
        }
        if (l < m_dictionary.size() && m_dictionary[l].substr(0, pref.size()) == pref) {
            int i = l + k - 1;
            if (i < m_dictionary.size() && m_dictionary[i].substr(0, pref.size()) == pref) return i + 1;
        }
        return -1;
    }

};

int main() {
    std::ios_base::sync_with_stdio(false);
    ifstream file_name("input.txt");
    Automatic f(file_name);
    ofstream out("output.txt");
    f.solve(out);
}

