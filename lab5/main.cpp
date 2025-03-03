#include <iostream>
#include "containers/myset.h"
#include "containers/myvector.h"

#include <string>

void main_legacy() {
    MyVector v("Hello!");
    v.add_element("Привет!");
    v.add_element("Привет!");
    v.add_element("Привет!");
    v.add_element("Привет!");
    v.add_element("Привет!");
    std::cout << "Вектор v: " << v << std::endl;
    v.add_element("Привет!");
    v.add_element("Привет!");
    v.add_element("Привет!");
    std::cout << "Вектор v: " << v << std::endl;
    MyVector v1 = v;
    std::cout << "Вектор v1: " << v1 << std::endl;
    for (int i = 0; i < v1.get_size(); i++)
        v1.delete_element(0);
    std::cout << "Вектор v1: " << v1 << std::endl;
    MySet<const char*> s("Yes"), s1, s2;
    s.add_element("Привет!");
    s.add_element("No");
#pragma clang diagnostic ignored "-Wwritable-strings"
    char* str = "Hello!";
    s.add_element(str);
    std::cout << "Множество s: " << s << std::endl;
    s1.add_element("Cat");
    s1.add_element("No");
    s1.add_element("Привет!");
    std::cout << "Множество s1: " << s1 << std::endl;
    s2 = s1 - s;
    std::cout << "Множество s2=s1-s: " << s2 << std::endl;
    std::cout << "Множество s1: " << s1 << std::endl;
    std::cout << "Множество s: " << s << std::endl;
    s2 = s - s1;
    std::cout << "Множество s2=s-s1: " << s2 << std::endl;
    std::cout << "Множество s1: " << s1 << std::endl;
    std::cout << "Множество s: " << s << std::endl;
    s2 = s1 + s;
    std::cout << "Множество s2=s1+s: " << s2 << std::endl;
    std::cout << "Множество s1: " << s1 << std::endl;
    std::cout << "Множество s: " << s << std::endl;
    s2 = s1 * s;
    std::cout << "Множество s2=s1*s: " << s2 << std::endl;
    std::cout << "Множество s1: " << s1 << std::endl;
    std::cout << "Множество s: " << s << std::endl;
    MySet s3 = s2;
    std::cout << "Множество s3=s2: " << s3 << std::endl;
    if (s3 == s2)
        std::cout << "Множество s3=s2\n";
    else
        std::cout << "Множество s3!=s2\n";
    if (s3 == s1)
        std::cout << "Множество s3=s1\n";
    else
        std::cout << "Множество s3!=s1\n";
    if (s1 == s3)
        std::cout << "Множество s1=s3\n";
    else
        std::cout << "Множество s1!=s3\n";
}

int main() {
    setlocale(LC_ALL, "Russian");

    main_legacy();
    std::cout << "-------------------" << std::endl;

    // проверка MyVector<int>
    MyVector<int> v(5);
    v.add_element(4);
    v.add_element(1);
    v.add_element(3);
    v.add_element(2);
    v.add_element(4);
    std::cout << "Вектор v: " << v << '\n';  // 5 4 1 3 2 4
    v.sort();
    std::cout << "Вектор v: " << v << '\n';  // 1 2 3 4 4 5
    v.delete_element(2);
    v.delete_element(2);
    std::cout << "Вектор v: " << v << '\n';                         // 1 2 4 5
    std::cout << "v.find(4): " << v.find(4) << '\n';                // 2
    std::cout << "v.find(4): " << v.find(3) << '\n';                // -1
    std::cout << "v.get_capacity(): " << v.get_capacity() << '\n';  // 8
    std::cout << "v.size(): " << v.get_size() << '\n';              // 4

    std::cout << "-------------------" << std::endl;

    // проверка MyVector<char*>
    char text[10][6] = {"AAA", "BB", "C", "D", "EEEEE", "F", "GG", "HI", "jk", "L"};
    MyVector<char*> v1(text[5]);
    v1.add_element(text[3]);
    v1.add_element(text[1]);
    v1.add_element(text[9]);
    v1.add_element(text[0]);
    v1.sort();
    MyVector<char*> v2(v1);
    v2.add_element(text[7]);
    v2.add_element(text[8]);
    std::cout << "Вектор v1: " << v1 << '\n';                       // AAA BB D F L
    std::cout << "Вектор v2: " << v2 << '\n';                       // AAA BB D F L HI jk
    std::cout << "v1.find(text[4]): " << v1.find(text[4]) << '\n';  // -1
    std::cout << "v1.find(text[5]): " << v1.find(text[5]) << '\n';  // 3

    std::cout << "-------------------" << std::endl;

    // Проверка MySet<int>
    MySet<int> A;
    A.add_element(1);
    A.add_element(2);
    A.add_element(5);
    A.add_element(4);
    MySet<int> B;
    B.add_element(2);
    B.add_element(3);
    B.add_element(5);
    B.add_element(6);

    std::cout << A << ' ' << B << '\n';  // 1 2 4 5  2 3 5 6
    std::cout << A + B << "\n";          // 1 2 3 4 5 6
    std::cout << A - B << "\n";          // 1 4
    std::cout << A * B << "\n";          // 2 5
    std::cout << A << ' ' << B << '\n';  // 1 2 4 5  2 3 5 6  <-- проверка что + - * не меняют A B

    A == B ? std::cout << "A == B" << '\n' : std::cout << "A != B" << '\n';  // A != B
    A = B;
    std::cout << A << ' ' << B << '\n';                                      // 2 3 5 6  2 3 5 6
    A == B ? std::cout << "A == B" << '\n' : std::cout << "A != B" << '\n';  // A == B
    A.delete_element(2);
    std::cout << A << ' ' << B << '\n';  // 3 5 6  2 3 5 6

    std::cout << "-------------------" << std::endl;

    // Проверка MySet<char*>
    MySet<char*> sA;
    for (int i = 0; i < 5; ++i) {
        char* str = new char[std::strlen(text[i])];
        std::strcpy(str, text[i]);
        sA.add_element(str);
        delete[] str;
    }
    MySet<char*> sB;
    for (int i = 3; i < 8; ++i) {
        char* str = new char[std::strlen(text[i])];
        std::strcpy(str, text[i]);
        sB.add_element(str);
        delete[] str;
    }

    std::cout << sA << " -- " << sB << '\n';  // AAA BB C D EEEEE  -- D EEEEE F GG HI
    std::cout << sA + sB << "\n";             // AAA BB C D EEEEE F GG HI
    std::cout << sA - sB << "\n";             // AAA BB C
    std::cout << sA * sB << "\n";             // D EEEEE

    std::cout << "-------------------" << std::endl;

    std::string str = "blablabla";
    MySet stringsA(str);
    str = "lalala";
    stringsA.add_element(str);
    str = "qweqwe";
    stringsA.add_element(str);

    MySet stringsB = stringsA;
    str = "reeeeeee";
    stringsA.add_element(str);
    str = "word";
    stringsA.add_element(str);

    std::cout << stringsA << " -- " << stringsB << '\n';  // blablabla lalala qweqwe reeeeeee word  -- blablabla lalala qweqwe
    std::cout << stringsA + stringsB << "\n";             // blablabla lalala qweqwe reeeeeee word
    std::cout << stringsA - stringsB << "\n";             // reeeeeee word
    std::cout << stringsA * stringsB << "\n";             // blablabla lalala qweqwe

    return 0;
}
