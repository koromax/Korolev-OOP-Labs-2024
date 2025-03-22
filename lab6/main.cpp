#include <iostream>

#include "Polynomial/Polynomial.h"

void TermTesting() {
    std::cout << Term("x") << " (should be x)" << '\n';
    std::cout << Term("1x") << " (should be x)" << '\n';
    std::cout << Term("x^1") << " (should be x)" << '\n';
    std::cout << Term("1x^1") << " (should be x)" << '\n';
    std::cout << Term("+1x^1") << " (should be x)" << '\n';
    std::cout << Term("+x^1") << " (should be x)" << '\n';

    std::cout << Term("-x^1") << " (should be -x)" << '\n';
    std::cout << Term("-x") << " (should be -x)" << '\n';
    std::cout << Term("-1x") << " (should be -x)" << '\n';

    std::cout << Term("-2x") << " (should be -2x)" << '\n';
    std::cout << Term("-52x^3") << " (should be -52x^3)" << '\n';
    std::cout << Term("1x^7245") << " (should be x^7245)" << '\n';
    std::cout << Term("413x") << " (should be 413x)" << '\n';
    std::cout << Term("-413x") << " (should be -413x)" << '\n';
    std::cout << Term("x^123") << " (should be x^123)" << '\n';

    std::cout << Term("1") << " (should be 1)" << '\n';
    std::cout << Term("+12348") << " (should be 12348)" << '\n';
    std::cout << Term("42x^0") << " (should be 42)" << '\n';
    std::cout << Term("-3x^0") << " (should be -3)" << '\n';
}

int main(int argc, char** argv) {
    Polynomial p1("3x^2 - x^2 -    3x^2 + x ^2 + 5x^5   - 4x^3 +x^2 - 7");
    Polynomial p2("0");
    if (argc > 1 && argv[1][0] == 'i') {
        std::cin >> p1;
        std::cin >> p2;
    } else if (argc > 1 && argv[1][0] == 't') {
        TermTesting();
        return 0;
    }

    std::cout << "p1     : " << p1 << '\n';
    std::cout << "p2     : " << p2 << '\n';
    std::cout << "p1 + p2: " << p1 + p2 << '\n';
    std::cout << "p1 * p2: " << p1 * p2 << '\n';

    return 0;
}
