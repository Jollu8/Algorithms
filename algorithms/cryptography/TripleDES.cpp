///// @Jollu
// Triple-DES algorithm



#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include <ctime>
#include <unordered_map>
#include <sstream>

class DES {
    static std::string xor_str(std::string &a, std::string &b);

public:
    DES();

    ~DES();

    static std::string hex_bin(std::string &s);

    static std::string bin_hex(std::basic_string<char> s);

    static std::string permute(std::string &key, int *arr, int n);

    static std::string shift_left(std::string &key, int shift);

    std::string encrypt_tool(std::string &plainText, std::vector<std::string> &rkb, std::vector<std::string> rkh);

    std::string triple_DES_encrypt(std::string &plainText);

    static std::string padding(std::string bloc);

    void func(std::string &plainText);
};

//// DES::triple_DES_encrypt
std::string DES::triple_DES_encrypt(std::string &plainText) {
    int PC1[56] = {57, 49, 41, 33, 25, 17, 9,
                   1, 58, 50, 42, 34, 26, 18,
                   10, 2, 59, 51, 43, 35, 27,
                   19, 11, 3, 60, 52, 44, 36,
                   63, 55, 47, 39, 31, 23, 15,
                   7, 62, 54, 46, 38, 30, 22,
                   14, 6, 61, 53, 45, 37, 29,
                   21, 13, 5, 28, 20, 12, 4};

    // PC2 table
    int PC2[48] = {14, 17, 11, 24, 1, 5,
                   3, 28, 15, 6, 21, 10,
                   23, 19, 12, 4, 26, 8,
                   16, 7, 27, 20, 13, 2,
                   41, 52, 31, 37, 47, 55,
                   30, 40, 51, 45, 33, 48,
                   44, 49, 39, 56, 34, 53,
                   46, 42, 50, 36, 29, 32};

    std::vector<std::string> table = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"};
    srand(time(nullptr));
    std::string key_1;
    std::string key_2;
    std::string key_3;

    // Random hexadecimal keys generator 16 Bytes (64 bits)
    while (key_1.length() != 16 && key_2.length() != 16 && key_3.length() != 16) {
        int x = std::rand() % 16;
        int y = std::rand() % 16;
        int z = std::rand() % 16;
        key_1 += table[x];
        key_2 += table[y];
        key_3 += table[z];
    }

    // ENCRYPTION WITH KEY_1
    key_1 = hex_bin(key_1); // hex to bin

    key_1 = permute(key_1, PC1, 56);

    int shift_table[16] = {1, 1, 2, 2,
                           2, 2, 2, 2,
                           1, 2, 2, 2,
                           2, 2, 2, 1};


    std::string left_1 = key_1.std::string::substr(0, 28);
    std::string right_1 = key_1.std::string::substr(28, 28);

    std::vector<std::string> RKB_1; // Round keys binary
    std::vector<std::string> RKH_1; // Round keys hexadecimal

    for (int i : shift_table) {
        left_1 = shift_left(left_1, i);
        right_1 = shift_left(right_1, i);

        std::string combined_1 = left_1 + right_1;

        std::string RoundKey_1 = permute(combined_1, PC2, 48);

        RKB_1.push_back(RoundKey_1);
        RKH_1.push_back(bin_hex(RoundKey_1));
    }
    std::string cipher = encrypt_tool(plainText, RKB_1, RKH_1);


    //DECRYPTION WITH KEY_2
    key_2 = hex_bin(key_2); // hex to bin

    key_2 = permute(key_2, PC1, 56);

    std::string left_2 = key_2.std::string::substr(0, 28);
    std::string right_2 = key_2.std::string::substr(28, 28);

    std::vector<std::string> RKB_2;
    std::vector<std::string> RKH_2;

    for (int i : shift_table) {
        left_2 = shift_left(left_2, i);
        right_2 = shift_left(right_2, i);

        std::string combined_2 = left_2 + right_2;

        std::string RoundKey_2 = permute(combined_2, PC2, 48);

        RKB_2.push_back(RoundKey_2);
        RKH_2.push_back(bin_hex(RoundKey_2));
    }
    std::reverse(RKB_2.begin(), RKB_2.end());
    std::reverse(RKH_2.begin(), RKH_2.end());
    std::string cipher_2 = encrypt_tool(cipher, RKB_2, RKH_2);


    //ENCRYPTION WITH KEY 3
    key_3 = hex_bin(key_3); // hex to bin

    key_3 = permute(key_3, PC1, 56);

    std::string left_3 = key_3.std::string::substr(0, 28);
    std::string right_3 = key_3.std::string::substr(28, 28);


    std::vector<std::string> RKB_3;
    std::vector<std::string> RKH_3;

    for (int i : shift_table) {
        left_3 = shift_left(left_3, i);
        right_3 = shift_left(right_3, i);

        std::string combined_3 = left_3 + right_3;

        std::string RoundKey_3 = permute(combined_3, PC2, 48);

        RKB_3.push_back(RoundKey_3);
        RKH_3.push_back(bin_hex(RoundKey_3));
    }
    std::string cipher_final = encrypt_tool(cipher_2, RKB_3, RKH_3);
    return cipher_final;
}

//// DES::bin_hex
std::string DES::bin_hex(std::basic_string<char> s) {
    std::unordered_map<std::string, std::string> dict;

    dict["0000"] = "0";
    dict["0001"] = "1";
    dict["0010"] = "2";
    dict["0011"] = "3";
    dict["0100"] = "4";
    dict["0101"] = "5";
    dict["0110"] = "6";
    dict["0111"] = "7";
    dict["1000"] = "8";
    dict["1001"] = "9";
    dict["1010"] = "A";
    dict["1011"] = "B";
    dict["1100"] = "C";
    dict["1101"] = "D";
    dict["1110"] = "E";
    dict["1111"] = "F";

    std::string hexadecimal;
    for (auto i(0); i < s.length(); i += 4) {
        std::string ch;
        ch += s[i];
        ch += s[i + 1];
        ch += s[i + 2];
        ch += s[i + 3];
        hexadecimal += dict[ch];
    }
    return hexadecimal;
}

//// DES::encrypt_tool
std::string DES::encrypt_tool(std::string &plainText, std::vector<std::string> &rkb, std::vector<std::string> rkh) {
    plainText = hex_bin(plainText);

    // Initial Permutation table
    int initial_perm[64] = {58, 50, 42, 34, 26, 18, 10, 2,
                            60, 52, 44, 36, 28, 20, 12, 4,
                            62, 54, 46, 38, 30, 22, 14, 6,
                            64, 56, 48, 40, 32, 24, 16, 8,
                            57, 49, 41, 33, 25, 17, 9, 1,
                            59, 51, 43, 35, 27, 19, 11, 3,
                            61, 53, 45, 37, 29, 21, 13, 5,
                            63, 55, 47, 39, 31, 23, 15, 7};

    plainText = permute(plainText, initial_perm, 64);
    std::string left = plainText.std::string::substr(0, 32);
    std::string right = plainText.std::string::substr(32, 32);

    // Expansion D-Box table
    int exp_d[48] = {32, 1, 2, 3, 4, 5, 4, 5,
                     6, 7, 8, 9, 8, 9, 10, 11,
                     12, 13, 12, 13, 14, 15, 16, 17,
                     16, 17, 18, 19, 20, 21, 20, 21,
                     22, 23, 24, 25, 24, 25, 26, 27,
                     28, 29, 28, 29, 30, 31, 32, 1};

    // S-Box table
    int S_Box[8][4][16] = {{14, 4,  13, 1,  2,  15, 11, 8,  3,  10, 6,  12, 5,  9,  0,  7,
                                   0,  15, 7,  4,  14, 2,  13, 1,  10, 6, 12, 11, 9,  5,  3,  8,
                                   4,  1,  14, 8,  13, 6,  2,  11, 15, 12, 9,  7,  3,  10, 5,  0,
                                   15, 12, 8,  2,  4,  9,  1,  7,  5,  11, 3,  14, 10, 0, 6,  13},

                           {15, 1,  8,  14, 6,  11, 3,  4,  9,  7,  2,  13, 12, 0,  5,  10,
                                   3,  13, 4,  7,  15, 2,  8,  14, 12, 0, 1,  10, 6,  9,  11, 5,
                                   0,  14, 7,  11, 10, 4,  13, 1,  5,  8,  12, 6,  9,  3,  2,  15,
                                   13, 8,  10, 1,  3,  15, 4,  2,  11, 6,  7,  12, 0,  5, 14, 9},

                           {10, 0,  9,  14, 6,  3,  15, 5,  1,  13, 12, 7,  11, 4,  2,  8,
                                   13, 7,  0,  9,  3,  4,  6,  10, 2,  8, 5,  14, 12, 11, 15, 1,
                                   13, 6,  4,  9,  8,  15, 3,  0,  11, 1,  2,  12, 5,  10, 14, 7,
                                   1,  10, 13, 0,  6,  9,  8,  7,  4,  15, 14, 3,  11, 5, 2,  12},

                           {7,  13, 14, 3,  0,  6,  9,  10, 1,  2,  8,  5,  11, 12, 4,  15,
                                   13, 8,  11, 5,  6,  15, 0,  3,  4,  7, 2,  12, 1,  10, 14, 9,
                                   10, 6,  9,  0,  12, 11, 7,  13, 15, 1,  3,  14, 5,  2,  8,  4,
                                   3,  15, 0,  6,  10, 1,  13, 8,  9,  4,  5,  11, 12, 7, 2,  14},

                           {2,  12, 4,  1,  7,  10, 11, 6,  8,  5,  3,  15, 13, 0,  14, 9,
                                   14, 11, 2,  12, 4,  7,  13, 1,  5,  0, 15, 10, 3,  9,  8,  6,
                                   4,  2,  1,  11, 10, 13, 7,  8,  15, 9,  12, 5,  6,  3,  0,  14,
                                   11, 8,  12, 7,  1,  14, 2,  13, 6,  15, 0,  9,  10, 4, 5,  3},

                           {12, 1,  10, 15, 9,  2,  6,  8,  0,  13, 3,  4,  14, 7,  5,  11,
                                   10, 15, 4,  2,  7,  12, 9,  5,  6,  1, 13, 14, 0,  11, 3,  8,
                                   9,  14, 15, 5,  2,  8,  12, 3,  7,  0,  4,  10, 1,  13, 11, 6,
                                   4,  3,  2,  12, 9,  5,  15, 10, 11, 14, 1,  7,  6,  0, 8,  13},

                           {4,  11, 2,  14, 15, 0,  8,  13, 3,  12, 9,  7,  5,  10, 6,  1,
                                   13, 0,  11, 7,  4,  9,  1,  10, 14, 3, 5,  12, 2,  15, 8,  6,
                                   1,  4,  11, 13, 12, 3,  7,  14, 10, 15, 6,  8,  0,  5,  9,  2,
                                   6,  11, 13, 8,  1,  4,  10, 7,  9,  5,  0,  15, 14, 2, 3,  12},

                           {13, 2,  8,  4,  6,  15, 11, 1,  10, 9,  3,  14, 5,  0,  12, 7,
                                   1,  15, 13, 8,  10, 3,  7,  4,  12, 5, 6,  11, 0,  14, 9,  2,
                                   7,  11, 4,  1,  9,  12, 14, 2,  0,  6,  10, 13, 15, 3,  5,  8,
                                   2,  1,  14, 7,  4,  10, 8,  13, 15, 12, 9,  0,  3,  5, 6,  11}
    };

    // Straight Permutation table
    int perm_table[32] = {16, 7, 20, 21,
                          29, 12, 28, 17,
                          1, 15, 23, 26,
                          5, 18, 31, 10,
                          2, 8, 24, 14,
                          32, 27, 3, 9,
                          19, 13, 30, 6,
                          22, 11, 4, 25};

    for (auto ii(0); ii < 16; ii++) {
        std::string right_expanded = permute(right, exp_d, 48);
        std::string x = xor_str(rkb[ii], right_expanded);

        std::string op;
        for (auto i(0); i < 8; i++) {
            int row = 2 * int(x[i * 6] - '0') + int(x[i * 6 + 5] - '0');
            int col = 8 * int(x[i * 6 + 1] - '0') + 4 * int(x[i * 6 + 2] - '0') + 2 * int(x[i * 6 + 3] - '0') +
                      int(x[i * 6 + 4] - '0');
            int val = S_Box[i][row][col];
            op += char(val / 8 + '0');
            val = val % 8;
            op += char(val / 4 + '0');
            val = val % 4;
            op += char(val / 2 + '0');
            val = val % 2;
            op += char(val + '0');
        }
        op = permute(op, perm_table, 32);
        x = xor_str(op, left);
        left = x;

        if (ii != 15) {
            swap(left, right);
        }
    }
    std::string combined = left + right;
    int final_perm[64] = {40, 8, 48, 16, 56, 24, 64, 32,
                          39, 7, 47, 15, 55, 23, 63, 31,
                          38, 6, 46, 14, 54, 22, 62, 30,
                          37, 5, 45, 13, 53, 21, 61, 29,
                          36, 4, 44, 12, 52, 20, 60, 28,
                          35, 3, 43, 11, 51, 19, 59, 27,
                          34, 2, 42, 10, 50, 18, 58, 26,
                          33, 1, 41, 9, 49, 17, 57, 25};

    std::string cipher = bin_hex(permute(combined, final_perm, 64));
    return cipher;
}

//// DES::hex_bin
std::string DES::hex_bin(std::string &s) {
    std::unordered_map<char, std::string> dict; // dictionary matching between hexadecimal and binary

    dict['0'] = "0000";
    dict['1'] = "0001";
    dict['2'] = "0010";
    dict['3'] = "0011";
    dict['4'] = "0100";
    dict['5'] = "0101";
    dict['6'] = "0110";
    dict['7'] = "0111";
    dict['8'] = "1000";
    dict['9'] = "1001";
    dict['A'] = "1010";
    dict['B'] = "1011";
    dict['C'] = "1100";
    dict['D'] = "1101";
    dict['E'] = "1110";
    dict['F'] = "1111";

    std::string binary_str;
    for (char & i : s) {
        binary_str += dict[i];
    }
    return binary_str;
}

//// DES::permute
std::string DES::permute(std::string &key, int *arr, int n) {
    std::string per;
    for (auto i = 0; i < n; i++) {
        per += key[arr[i] - 1];
    }
    return per;
}

//// DES::shift_left
std::string DES::shift_left(std::string &key, int shift) {
    std::string s;
    for (auto i(0); i < shift; i++) {
        for (auto j(0); j < 28; j++)s += key[i];
        s += key[0];
        key = s;
        s = "";
    }
    return key;
}

//// DES::xor_str
std::string DES::xor_str(std::string &a, std::string &b) {
    std::string res;
    for (auto i(0); i < a.size(); ++i) {
        if (a[i] == b[i]) res += "0";
        else res += "1";
    }
    return res;
}

//// DES::func
void DES::func(std::string &plainText) {
    std::string bloc;
    std::string hex_str;
    for (char i : plainText) {
        std::stringstream my_ps;
        my_ps << std::uppercase << std::hex << int(i);
        hex_str += my_ps.str();
    }
    if (hex_str.size() <
        16) { // If size of the hex_str text is less than 16 (64 bits); pad with random hexadecimal character
        std::cout << std::endl << "[ Encrypted Text ] -> ";
        hex_str = padding(hex_str);
        std::cout << triple_DES_encrypt(hex_str);
        std::cout << std::endl << std::endl;
    } else if (hex_str.size() > 16) { // ECB mode (Crack the message in 64 bits each - 16 hexadecimal numbers)
        std::cout << std::endl << "[ Encrypted Text ] -> ";
        for (auto i(0); i < hex_str.size(); i += 16) {
            bloc = hex_str.substr(i, 16);
            if (bloc.size() <
                16) { // If size of the final bloc is less than 16 (64 bits); pad the bloc with random hexadecimal character
                bloc = padding(bloc);
            }
            std::cout << triple_DES_encrypt(bloc) << "  ";
        }
        std::cout << std::endl << std::endl;
    } else { // If hex_str size == 16 (64 bits)
        std::cout << std::endl << "[ Encrypted Text ] -> " << triple_DES_encrypt(hex_str) << std::endl << std::endl;
    }
    }


std::vector<std::string> pad_table = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"};

std::string DES::padding(std::string bloc) {
    srand(time(nullptr));
    do {
        int x = rand() % 16;
        bloc += pad_table[x];
    } while (bloc.size() != 16);
    return bloc;
}

DES::DES() = default;

DES::~DES() = default;


int main() {

    DES des;
    system("clear");

    std::string plaintext;
    std::cout << std::endl << "[ Clear Text ] -> ";
    std::getline(std::cin, plaintext);

    srand(time(nullptr));

    for (auto i = plaintext.length() - 1; i > 0; i--) {
        int j = std::rand() % (i + 1);
        std::swap(plaintext[i], plaintext[j]);
    }

    des.func(plaintext);

    return 0;
}