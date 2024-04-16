///// @Jollu
// Caesar Cipher



#include <cctype>
#include <string>
#include <cstdint>
#include <iostream>

std::string encrypt(const std::string &text, std::uint8_t key) {
    std::string encryptedText = std::move(text);
    for (auto &symbol: encryptedText) {
        if (std::isupper(symbol))
            symbol = static_cast<char >((symbol + key) <= 'Z' ? (symbol + key) : (symbol + key) - ('Z' - 'A' + 1));

        if (std::islower(symbol))
            symbol = static_cast<char >((symbol + key) <= 'z' ? (symbol + key) : 'z' - 'a' + 1);
    }
    return encryptedText;
}

std::string decrypt(const std::string &text, std::uint8_t key) {
    std::string decryptText = std::move(text);
    for (auto &symbol: decryptText) {
        if (std::isupper(symbol))
            symbol = static_cast<char >((symbol - key) >= 'A' ? (symbol - key) : (symbol - key) - ('Z' - 'A') + 1);
        if (std::islower(symbol))
            symbol = static_cast<char >((symbol - key) >= 'a' ? (symbol - key) : ('z' - 'a' + 1));
    }
    return decryptText;

}


int main() {
    const std::uint8_t key = 2;
    const std::string text = "Test text...";
    auto encryptT = encrypt(text, key);
    std::cout << decrypt(encryptT, key);

}