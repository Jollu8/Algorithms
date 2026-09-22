///// @Jollu
// RSA Algorithm

#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
#include <cstdio>


bool isPrime(long int prime);

long int calculateE(long int t);

long int greatestCommonDivisor(long int e, long int t);

long int calculateD(long int e, long int t);

long int encrypt(long int i, long int e, long int n);

long int decrypt(long int i, long int d, long int n);

int main() {
    long int p, q, n, t, e, d;

    long int encryptedText[100];
    memset(encryptedText, 0, sizeof(encryptedText));

    long int decryptedText[100];
    memset(decryptedText, 0, sizeof(decryptedText));

    bool flag;

    std::string msg;

    std::cout << "Welcome to RCA program" << std::endl << std::endl;

    // Создания открытого и секретного ключей

    // 1. Выбираются два различных случайных простых числа p и q заданного размера

    do {
        std::cout << "Enter a Prime number  p :" << std::endl;
        std::cin >> p;
        flag = isPrime(p);

        if (!flag) {
            std::cout
                    << "\nWRONG INPUT (This number is not Prime. A prime number is a natural number greater than 1 that has no positive divisors other than 1 and itself)\n"
                    << std::endl;
        }
    } while (!flag);


    do {
        std::cout << "Enter a Prime number  q :" << std::endl;
        std::cin >> q;
        flag = isPrime(q);

        if (!flag) {
            std::cout
                    << "\nWRONG INPUT (This number is not Prime. A prime number is a natural number greater than 1 that has no positive divisors other than 1 and itself)\n"
                    << std::endl;
        }
    } while (!flag);

    // 2. Вычисляется их произведение n = p ⋅ q, которое называется модулем.
    n = p * q;
    std::cout << "\nResult of computing n = p*q = " << n << std::endl;

    // 3. Вычисляется значение функции Эйлера от числа n: φ(n) = (p−1)⋅(q−1)
    t = (p - 1) * (q - 1);
    std::cout << "Result of computing Euler's totient function:\t t = " << t << std::endl;

    // 4. Выбирается целое число e ( 1 < e < φ(n) ), взаимно простое со значением функции Эйлера (t)
    //	  Число e называется открытой экспонентой
    e = calculateE(t);

    // 5. Вычисляется число d, мультипликативное обратное к числу e по модулю φ(n), то есть число, удовлетворяющее сравнению:
    //    d ⋅ e ≡ 1 (mod φ(n))
    d = calculateD(e, t);

    // 6. Пара {e, n} публикуется в качестве открытого ключа RSA
    std::cout << "\nRSA public key is (n = " << n << ", e = " << e << ")" << std::endl;

    // 7. Пара {d, n} играет роль закрытого ключа RSA и держится в секрете
    std::cout << "RSA private key is (n = " << n << ", d = " << d << ")" << std::endl;


    std::cout << "\nEnter Message to be encrypted:" << std::endl;

    // there is a newline character left in the input stream, so we use ignore()
    std::cin.ignore();

    std::getline(std::cin, msg);

    std::cout << "\nThe message is: " << msg << std::endl;


    // encryption

    for (long int i = 0; i < msg.length(); i++) {
        encryptedText[i] = encrypt(msg[i], e, n);
    }

    std::cout << "\nTHE ENCRYPTED MESSAGE IS:" << std::endl;

    for (long int i = 0; i < msg.length(); i++) {
        printf("%c", (char) encryptedText[i]);
    }


    //decryption

    for (long int i = 0; i < msg.length(); i++) {
        decryptedText[i] = decrypt(encryptedText[i], d, n);
    }

    std::cout << "\n\nTHE DECRYPTED MESSAGE IS:" << std::endl;

    for (long int i = 0; i < msg.length(); i++) {
        printf("%c", (char) decryptedText[i]);
    }


    std::cout << std::endl << std::endl;

    //system("PAUSE");

    return 0;
}

bool isPrime(long int prime) {
    long int i, j;

    j = static_cast<long int>(sqrt(static_cast<long double>(prime)));

    for (i = 2; i <= j; i++) {
        if (prime % i == 0) {
            return false;
        }
    }

    return true;
}

long int calculateE(long int t) {
    // Выбирается целое число e ( 1 < e < t ) // взаимно простое со значением функции Эйлера (t)

    long int e;

    for (e = 2; e < t; e++) {
        if (greatestCommonDivisor(e, t) == 1) {
            return e;
        }
    }

    return -1;
}

long int greatestCommonDivisor(long int e, long int t) {
    while (e > 0) {
        long int myTemp;

        myTemp = e;
        e = t % e;
        t = myTemp;
    }

    return t;
}

long int calculateD(long int e, long int t) {
    // Вычисляется число d, мультипликативное обратное к числу e по модулю φ(n), то есть число, удовлетворяющее сравнению:
    //    d ⋅ e ≡ 1 (mod φ(n))

    long int d;
    long int k = 1;

    while (true) {
        k = k + t;

        if (k % e == 0) {
            d = (k / e);
            return d;
        }
    }

}


long int encrypt(long int i, long int e, long int n) {
    long int current, result;

    current = i - 97;
    result = 1;

    for (long int j = 0; j < e; j++) {
        result = result * current;
        result = result % n;
    }

    return result;
}

long int decrypt(long int i, long int d, long int n) {
    long int current, result;

    current = i;
    result = 1;

    for (long int j = 0; j < d; j++) {
        result = result * current;
        result = result % n;
    }

    return result + 97;
}
