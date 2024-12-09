//
// Created by Jollu Emil on 8/7/24.
//

#pragma once
#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    int r, c;
    std::cin >> r >> c;
    std::cin.ignore();

    std::vector<std::string> crossword(r);

    for (int i = 0; i < r; i++) {
        std::getline(std::cin, crossword[i]);
    }

    std::vector<std::string> allWords;

    for (int i = 0; i < r; i++) {
        std::string row = crossword[i];
        size_t pos = 0;
        while ((pos = row.find('#')) != std::string::npos) {
            std::string word = row.substr(0, pos);
            if (word.length() >= 2) {
                allWords.push_back(word);
            }
            row.erase(0, pos + 1);
        }
        if (row.length() >= 2) {
            allWords.push_back(row);
        }
    }

    for (int j = 0; j < c; j++) {
        std::string colWord;
        for (int i = 0; i < r; i++) {
            char ch = crossword[i][j];

            if (ch == '#') {
                if (colWord.length() >= 2) {
                    allWords.push_back(colWord);
                }
                colWord = "";
            } else {
                colWord += ch;
            }
        }

        if (colWord.length() >= 2) {
            allWords.push_back(colWord);
        }
    }

    std::sort(allWords.begin(), allWords.end());
    std::cout << allWords[0] << std::endl;

    return 0;
}
