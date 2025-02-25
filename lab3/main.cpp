#include <iostream>

#include "fraction/fraction.h"

void TestFractionOperations() {
    fraction::fraction fr1("-1 1/2");
    fraction::fraction fr2(1, 2);

    // Test addition
    fraction::fraction frAdd = fr1 + 2.5;
    std::cout << "Addition: " << fr1.improperForm() << " + " << 2.5 << " = " << frAdd << '\n';

    // Test subtraction
    fraction::fraction frSub = fr1 - 2.5;
    std::cout << "Subtraction: " << fr1.improperForm() << " - " << 2.5 << " = " << frSub << '\n';

    // Test multiplication
    fraction::fraction frMul = fr1 * 2.5;
    std::cout << "Multiplication: " << fr1.improperForm() << " * " << 2.5 << " = " << frMul << '\n';

    // Test division
    fraction::fraction frDiv = fr1 / 2.5;
    std::cout << "Division: " << fr1.improperForm() << " / " << 2.5 << " = " << frDiv << '\n';
}

int main_test() {
    // ввод дроби с клавиатуры
    std::cout << "Введите дробь: \n";
    fraction::fraction z;
    std::cin >> z;
    std::cout << "z=" << z << std::endl;
    // проверка конструкторов
    fraction::fraction fr1(10, 14), fr2;
    std::cout << "fr2=" << fr2 << std::endl;
    std::cout << "fr1=" << fr1 << std::endl;
    fraction::fraction fr = "-1 4/8";
    std::cout << "fr=" << fr << std::endl;
    fraction::fraction x(z), y;
    std::cout << "x=" << x << std::endl;
    double dbl = -1.25;
    fraction::fraction f = dbl;
    std::cout << "f=" << f << std::endl;
    // проверка перегруженной операции "+"
    y = x + z;
    std::cout << "y=" << y << std::endl;
    y += x;
    f += dbl / 2;
    std::cout << "f=" << f << std::endl;
    y = x + dbl;
    std::cout << "y=" << y << std::endl;
    y = dbl + y;
    std::cout << "y=" << y << std::endl;
    y += dbl;
    std::cout << "y=" << y << std::endl;
    int i = 5;
    y += i;
    std::cout << "y=" << y << std::endl;
    y = i + x;
    std::cout << "y=" << y << std::endl;
    y = x + i;
    std::cout << "y=" << y << std::endl;
    y += dbl + i + x;
    std::cout << "y=" << y << std::endl;
    return 0;
}

int main() {
    // TestFractionOperations();

    main_test();
    return 0;
}
