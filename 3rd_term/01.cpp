#include <iostream>
#include <cstring>

const int MAX_LEN = 101;

char* right(char* s, int k) {
    int length = strlen(s);
    if (k < 0) {
        static char no[] = "";
        return no;
    }
    if (length <= k) return s;
    return s + length - k;
}

unsigned long right(unsigned long x, int k) {
    if (k < 0) return 0;
    unsigned long long power = 1;
    for (int i = 0; i < k; ++i) power *= 10;
    if (x < power) return x;
    return x % power;
}

int main() {
    char line[MAX_LEN];
    int k;
    unsigned long numb;

    std::cin.getline(line, MAX_LEN);
    if (std::strcmp(line, "string") == 0) {
        std::cin.getline(line, MAX_LEN);
        std::cin >> k;
        std::cout << right(line, k) << std::endl;
    } else {
        if (!(std::cin >> numb)) {
            std::cout << 0 << std::endl;
        } else {
            std::cin >> k;
            if (k < 0) {
                std::cout << 0 << std::endl;
            } else {
                std::cout << right(numb, k) << std::endl;
            }
        }
    }
    return 0;
}
