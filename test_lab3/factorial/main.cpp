#include <iostream>

unsigned long long factorial(int n) {
    // Базовый случай рекурсии
    if (n == 0 || n == 1) {
        return 1;
    }

    // Рекурсивный случай
    return n * factorial(n - 1);
}

int main() {
    unsigned long long fact = factorial(11);
    unsigned long long fact1 = factorial(10);
    unsigned long long fact2 = factorial(12);
    unsigned long long fact3 = factorial(13);
    unsigned long long fact4 = factorial(14);
    unsigned long long fact5 = factorial(16);
    std::cout << fact << fact1 << fact2 << fact3 << fact4 << fact5 << std::endl;
    return 0;
}