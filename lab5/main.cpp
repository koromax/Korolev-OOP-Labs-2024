#include <iostream>
#include "containers/myset.h"
#include "containers/myvector.h"

void check() {
    MyVector v(1.);
    v.add_element(2);
    MyVector v1 = v;
    v1.add_element(233);
    v1 = v;
    v.add_element(2);
    v.add_element(0.2);
    v.add_element(-3.1);
    v.add_element(2.001);
    std::cout << "Вектор v: " << v << std::endl;
    v.sort();
    v.delete_element(3);
    std::cout << v.find(0.2) << '\n';
    std::cout << "Вектор v: " << v << std::endl;
    std::cout << "Вектор v1: " << v1 << std::endl;

    MyVector s("Jopa");
    s.add_element("ass");
    s.add_element("kms");
    s.add_element(":P");
    s.sort();
    std::cout << s.find("ass") << ' ' << s.find("xD") << '\n';
    std::cout << "Вектор s: " << s << std::endl;
}

void check_set() {
    MySet<double> s;
    s.add_element(1.);
    s.add_element(1);
    s.add_element(1.01);
    s.add_element(2.01);
    s.add_element(-2.01);
    s.delete_element(1);
    s.delete_element(1);
    std::cout << s << '\n';

    MySet s1("brhu");
    s1.add_element("bruh");
    s1.add_element("skidibi");
    s1.add_element("skidibi");
    s1.add_element("T_T");
    std::cout << s1 << '\n';

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

    std::cout << A << ' ' << B << '\n';
    std::cout << A + B << "\n";
    std::cout << A - B << "\n";
    std::cout << A * B << "\n";

    std::cout << A << ' ' << B << '\n';
    A == B ? std::cout << "A == B" << '\n' : std::cout << "A != B" << '\n';
    A = B;
    std::cout << A << ' ' << B << '\n';
    A == B ? std::cout << "A == B" << '\n' : std::cout << "A != B" << '\n';
    A.delete_element(2);
    std::cout << A << ' ' << B << '\n';
}

void interactive() {
    MyVector<char*> v;
    char buffer[256];
    std::cin >> buffer;
    v.add_element(buffer);
    std::cout << v << '\n';
}

int main() {
    setlocale(LC_ALL, "Russian");

    check_set();
    // check();
    // interactive();
    // return 0;

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
    // return 0;

    MySet s("Yes");
    MySet<const char*> s1;
    MySet<const char*> s2;
    s.add_element("Привет!");
    s.add_element("No");
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
    return 0;
}
