//
// Created by jollu.
//
//RC4 Algorithm

#include <string>
#include <vector>
#include <iostream>

std::string decrypt(std::vector<int> &s, std::vector<int> &t, std::string &p) {
    std::size_t i = 0;
    std::size_t j = 0;
    std::size_t tmp = 0;
    std::size_t k = 0;

    std::size_t b, c;

    int *plain = new int[p.size()];

    std::string plain_t;
    for (auto r(0); r < p.size(); r++) {
        i = (i + 1) % 256;
        j = (j + s[i]) % 256;

        b = s[i];
        s[i] = s[j];
        s[j] = b;

        tmp = s[i] + s[j] % 256;
        k = s[tmp];

        c = ((int) p[r] ^ k);
        plain_t += (char) (plain[r]);
    }
    return plain_t;
}

std::string encrypt(std::vector<int> &s, std::vector<int> &t, std::string &p) {
    std::size_t i = 0;
    std::size_t j = 0;
    std::size_t tmp = 0;
    std::size_t k = 0;

    std::size_t b, c;

    int *cipher = new int[p.size()];
    std::string cipher_t;
    std::cout << "Keys Generated for plaintext: ";
    for (auto r(0); r < p.size(); ++r) {
        i = (i + 1) % 256;
        j = (j + s[i]) % 256;

        b = s[i];
        s[i] = s[j];
        s[j] = b;
        tmp = (s[i] + s[j]) % 256;
        k = s[tmp];
        std::cout << k << " ";
        c = ((int) p[r] ^ k);
        cipher[r] = c;
        cipher_t += (char) cipher[r];
    }
    std::cout << std::endl;
    return cipher_t;
}

std::vector<int> permute(std::vector<int> &s, std::vector<int> &t) {
    std::size_t j = 0, tmp;
    for (auto i(0); i < 256; ++i) {
        j = (j + s[i] + t[i]) % 256;
        tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }
    return s;
}

int main() {
    std::string plainText1 = "enc";
    std::string plainText2 = "RC4";

    std::vector<int> v1(256);
    std::vector<int> v2(256);

    int key1[] = {1, 2, 3, 6};
    int key2[] = {5, 7, 8, 9};

    [[maybe_unused]] int tmp = 0;
    for (auto i(0); i < 256; i++) {
        v1[i] = i;
        v2[i] = key1[(i % (sizeof(key1) / sizeof(*key1)))];
    }

    v1 = permute(v1, v2);
    for (auto i(0); i < 256; i++) {
        std::cout << v1[i] << " ";
        if ((i + 1) % 16 == 0) std::cout << std::endl;
    }
    std::cout << std::endl;
    std::string p = encrypt(v1, v2, plainText1);
    std::cout << "Message: " << plainText1 << std::endl;
    std::cout << "Encrypted message: " << " " << p << std::endl;
    std::cout << "Decrypted message: " << decrypt(v1, v2, p) << std::endl;

    tmp = 0;
    for (auto i(0); i < 256; i++) {
        v1[i] = i;
        v2[i] = key2[(i % (sizeof(key1) / sizeof(*key1)))];

    }
    v1 = permute(v1, v2);
    for (auto i(0); i < 256; i++) {
        std::cout << v1[i] << " ";
        if ((i + 1) % 16 == 0) std::cout << std::endl;
    }
    std::cout << std::endl;
    p = encrypt(v1, v2, plainText2);
    std::cout << "message: " << plainText2 << std::endl;
    std::cout << "Encrypted message: " << p << std::endl;
    std::cout << "Decrypted message: " << decrypt(v1, v2, p) << std::endl;
}


