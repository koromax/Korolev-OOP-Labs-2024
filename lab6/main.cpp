#include <iostream>

#include "Polynomial/Polynomial.h"

int main(int argc, char** argv) {
    Polynomial p1("9 -0");
    Polynomial p2("x^0     +1x");
    if (argc > 1 && argv[1][0] == 'i') {
        std::cin >> p1;
        std::cin >> p2;
    }
    // std::cout << p1 << '\n';

    // Polynomial p1("x^1 - 2x^3 + 5x^4");
    // Polynomial p2("2 + 4x^1 + 2x^3 + x^4");

    // https://www.wolframalpha.com/input?i=%28x%5E1+-+2x%5E3+%2B+5x%5E4%29+*+%282+%2B+4x%5E1+%2B+2x%5E3+%2B+x%5E4%29
    std::cout << "p1     : " << p1 << '\n';
    std::cout << "p2     : " << p2 << '\n';
    std::cout << "p1 + p2: " << p1 + p2 << '\n';
    std::cout << "p1 * p2: " << p1 * p2 << '\n';

    return 0;
}
