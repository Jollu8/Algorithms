
#include <fstream>
#include <string>
#include <algorithm>
#include <set>
#include <vector>
#include <utility>


// TL test 19

class Platformer {
public:

public:
    explicit Platformer(std::ifstream &in) {
        in >> N >> commands;
        states = std::vector<std::pair<int, int> >(N + 1);
        states[0] = {0, 1};
        calculateStates();
    }

    void solve(std::ofstream &out) {
        char possib[] = {'F', 'L', 'R'};
        for (int i = 0; i < N; ++i) {
            for (auto new_c: possib) {
                auto [pos, dir] = states[i];
                if (commands[i] != new_c) {
                    if (new_c == 'F') pos += dir;
                    else if (new_c == 'L') dir = -1;
                    else if (new_c == 'R') dir = 1;

                    // Simulate the possible command without modifying states
                    for (int j = i + 1; j < N; ++j) {
                        char c = commands[j];
                        if (c == 'F') pos += dir;
                        else if (c == 'L') dir = -1;
                        else if (c == 'R') dir = 1;
                    }
                    ans.insert(pos);
                }
            }
        }
        out << ans.size() << '\n';
    }


private:
    void calculateStates() {
        for (int i = 0; i < N; ++i) {
            char c = commands[i];
            auto [new_pos, new_dir] = states[i];

            if (c == 'F') new_pos += new_dir;
            else if (c == 'L') new_dir = -1;
            else if (c == 'R') new_dir = 1;
            states[i + 1] = {new_pos, new_dir};
        }
    }

private:
    int N;
    std::string commands;
    std::set<int> ans;
    std::vector<std::pair<int, int>> states;
};


int main() {
    std::ios_base::sync_with_stdio(false);
    std::ofstream out("output.txt");
    std::ifstream in("input.txt");
    Platformer p(in);
    p.solve(out);

}