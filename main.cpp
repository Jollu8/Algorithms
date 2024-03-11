#include <iostream>
#include <set>
#include <string>

using namespace std;

set<string> dict;
multiset<pair<string, string> > d_p;


bool big(char c) {
    if (c >= 65 && c <= 90) return true;
    return false;
}

string convert(string s) {
    for (int i = 0; i < s.length(); i++)
        if (big(s[i])) s[i] = s[i] + ('a' - 'A');
    // std::cout << s << std::endl;
    return s;
}

bool check(string s) {
    int r = 0;
    for (int i = 0; i < s.length(); i++)
        if (big(s[i])) r++;
    if (r == 1) return true;
    return false;
}

int main() {
    int n;
    cin >> n;
    int x = n;
    string s;
    for (int i = 0; i < n; i++) {
        cin >> s;
        d_p.insert(make_pair(convert(s), s));
        dict.insert(convert(s));
    }

    int r = 0;
    while (std::cin >> s) {
        if (dict.find(convert(s)) == dict.end()) {
            if (!check(s)) {
                std::cout << s << " ";
                r++;
            }
        } else if (d_p.find(make_pair(convert(s), s)) == d_p.end()) r++;
    }
    cout << r;
}
