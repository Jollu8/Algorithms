//
// Created by Jollu Emil on 8/7/24.
//

#pragma once
#pragma GCC optimize("O3")

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string_view>
#include <string>
#include <memory>
#include <vector>
#include <utility>


using namespace std;

class Formatting {
public:
    explicit Formatting(ifstream &in) : m_len(0) {
        getline(in, m_line);
        this->m_len = get_len();
        get_words();
    }

    void solve(ofstream &out) {
        string ans;
        bool e = true;
        for (auto &w: m_words) {
            if (ans.size() + 1 + w.size() > m_len) {
                out << ans << '\n';
                ans = "";
                e = true;
            }
            if (e)e = false;
            else ans += " ";
            ans += w;
        }
        if (ans.back() == ' ') ans.pop_back();
        out << ans << '\n';
    }

private:
    string m_line;
    long m_len;
    vector<string> m_words;

    long get_len() {
        long cnt{};
        for (char i : m_line) {
            if (i != ' ' && i != ',') ++cnt;
            else m_len = max(m_len, cnt), cnt = 0;
        }
        m_len = max(m_len, cnt);
        return 3 * m_len;
    }

    void get_words() {
        string w;
        for (int i = 0; i < m_line.size(); ++i) {
            if(m_line[i] == ' ') {
            if(!w.empty()) {
                m_words.push_back(std::move(w));
            }
            }else if(m_line[i] == ',') {
                if(m_line[i-1] == ' ')m_words.back() += ",";
                else  {
                    w += ",";
                    m_words.push_back(std::move(w));
                }
            }else w += m_line[i];
        }
        m_words.emplace_back(w);
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    ifstream file_name("input.txt");
    Formatting f(file_name);
    ofstream out("output.txt");
    f.solve(out);
}
