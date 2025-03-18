#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <random>
#include <vector>

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_int_distribution<> distr(0, 100);

void Task1() {
    /* 14. Пользователь вводит текст. Вывести на экран номера позиций в которых встречается символ @. */
    std::string s;
    std::cout << "Enter string that contains '@': ";
    std::getline(std::cin, s);
    auto i = std::find(s.begin(), s.end(), '@');
    while (i != s.end()) {
        std::cout << std::distance(s.begin(), i) + 1 << ' ';
        i = std::find(i + 1, s.end(), '@');
    }
    std::cout << '\n';
}

void Task2() {
    /* 14. Пользователь вводит некоторый текст. Образовать новую последовательность, включив в нее символы исходной в обратном порядке. */
    std::string s;
    std::cout << "Enter any non-fully whitespace character string: ";
    std::getline(std::cin, s);
    std::string sReversed = s;
    std::reverse(sReversed.begin(), sReversed.end());
    s += sReversed;
    std::cout << s << '\n';
}

void Task3() {
    /* 14. Дан текстовый файл. Запишите в другой файл содержимое исходного файла, чтобы каждое слово исходного файла было в отдельной строке. */
    std::ifstream in("lab8/3A.txt", std::ios::in);
    std::ofstream out("lab8/3B.txt", std::ios::out | std::ios::trunc);
    if (!in.is_open() || !out.is_open()) {
        std::cout << "At least one file has failed to open." << '\n';
        return;
    }

    std::string line;
    while (!in.eof()) {
        std::getline(in, line);

        std::size_t L = 0;
        std::size_t R = 0;
        while ((R = line.find(' ', L)) != std::string::npos) {
            out << line.substr(L, R - L) << '\n';
            L = R + 1;
        }
        out << line.substr(L, R) << '\n';
    }

    in.close();
    out.close();
    std::cout << "Completed Task 3" << '\n';
}

void doubleNumber(int& n) {
    n *= 2;
}
void printVector(std::vector<int> n) {
    for (auto e : n) {
        std::cout << e << ' ';
    }
    std::cout << '\n';
}
void Task4() {
    /* 4. Создать вектор из 5-ти целых случайных чисел (0 - 100). Распечатать.
    Удвоить каждое число в векторе. Распечатать.
    Удалить из вектора элемент с индексом 2 и снова распечатать вектор.
    Переделать программу: удвоение сделать с помощью функции и печатать вектор с помощью функции. */

    std::vector<int> n(5);
    for (int i = 0; i < n.size(); ++i) {
        n[i] = distr(gen);
    }
    std::vector<int> nCopy(n);
    for (auto e : n) {
        std::cout << e << ' ';
    }
    std::cout << '\n';

    for (int i = 0; i < n.size(); ++i) {
        n[i] *= 2;
    }
    for (auto e : n) {
        std::cout << e << ' ';
    }
    std::cout << '\n';

    n.erase(n.begin() + 2);
    for (auto e : n) {
        std::cout << e << ' ';
    }
    std::cout << '\n';

    std::cout << '\n';

    printVector(nCopy);
    std::for_each(nCopy.begin(), nCopy.end(), doubleNumber);
    printVector(nCopy);
    nCopy.erase(nCopy.begin() + 2);
    printVector(nCopy);
}

class Complex {
 public:
    double real = 0.;
    double imaginary = 0.;
    Complex(double r = 0., double i = 0.) : real(r), imaginary(i) {}
};
void Task5() {
    /* 4. Составить описание класса Complex для представления комплексных чисел с возможностью задания вещественной и мнимой частей числами типа
    double. В программе создать вектор из объектов класса Complex (6 элементов): ...
    Распечатать вектор в виде:
    -1.2 + i * 6.3
    ...
    Сложите все числа (у комплексных чисел отдельно складываются действительные и мнимые части) и результирующее число выведите на экран. */

    std::vector<Complex> c = {Complex(-1.2, 6.3), Complex(4.1, 0.7), Complex(7.2, -0.8), Complex(5.3, 3.0), Complex(-4.9, 6.6), Complex(-9.3, 0.2)};
    Complex result = Complex(0., 0.);
    for (auto e : c) {
        std::cout << e.real;
        if (e.imaginary >= 0) {
            std::cout << " + ";
        } else {
            std::cout << " - ";
        }
        std::cout << "i * " << std::abs(e.imaginary) << '\n';
        result.real += e.real;
        result.imaginary += e.imaginary;
    }
    std::cout << '\n';
    std::cout << "sum = " << result.real;
    if (result.imaginary >= 0) {
        std::cout << " + ";
    } else {
        std::cout << " - ";
    }
    std::cout << "i * " << std::abs(result.imaginary) << '\n';
}

void lPrint(std::list<int>& l) {
    std::list<int>::iterator iter;
    int i = 0;
    if (!l.empty()) {
        for (iter = l.begin(), i = 0; iter != l.end(); iter++, i++) {
            std::cout << *iter << ' ';
        }
        std::cout << '\n';
    } else
        std::cout << "Список пуст!" << std::endl;
}
void Task6() {
    /* 4. Создать контейнер из 5-ти целых случайных чисел (0 - 100). Распечатать.
    Удвоить каждое число в контейнере. Распечатать.
    Удалить из контейнера элемент с индексом 2 и снова распечатать контейнер.
    Переделать программу: удвоение сделать с помощью функции и печатать контейнер с помощью функции. */

    std::list<int>::iterator iter;
    int i = 0;
    std::list<int> l(5);
    for (iter = l.begin(); iter != l.end(); iter++) {
        *iter = distr(gen);
    }
    std::list<int> lCopy = l;
    for (iter = l.begin(), i = 0; iter != l.end(); iter++, i++) {
        std::cout << *iter << ' ';
    }
    std::cout << '\n';
    for (iter = l.begin(); iter != l.end(); iter++) {
        *iter *= 2;
    }
    for (iter = l.begin(), i = 0; iter != l.end(); iter++, i++) {
        std::cout << *iter << ' ';
    }
    std::cout << '\n';
    iter = l.begin();
    iter++;
    iter++;
    l.erase(iter);
    for (iter = l.begin(), i = 0; iter != l.end(); iter++, i++) {
        std::cout << *iter << ' ';
    }
    std::cout << '\n';

    std::cout << '\n';

    lPrint(lCopy);
    std::for_each(lCopy.begin(), lCopy.end(), doubleNumber);
    lPrint(lCopy);
    iter = lCopy.begin();
    iter++;
    iter++;
    lCopy.erase(iter);
    lPrint(lCopy);
}

class Rectangle {
 public:
    double a = 0.;  // ширина
    double b = 0.;  // длина
    Rectangle(double a = 0., double b = 0.) : a(a), b(b) {}

    friend bool operator<(const Rectangle& lhs, const Rectangle& rhs) { return (lhs.a * lhs.b) < (rhs.a * rhs.b); }
    friend bool operator==(const Rectangle& lhs, const Rectangle& rhs) { return (lhs.a == rhs.a) && (lhs.b == rhs.b); }
};
void rectPrint(std::list<Rectangle>& l) {
    std::list<Rectangle>::iterator iter;
    for (iter = l.begin(); iter != l.end(); iter++) {
        std::cout << std::setw(5) << (*iter).a << ' ' << std::setw(5) << (*iter).b << "    = " << std::setw(10) << (*iter).a * (*iter).b << '\n';
    }
    std::cout << '\n';
}
void Task7() {
    std::cout << std::left;
    /* 4. Создать список объектов типа Rectangle с помощью контейнера list в main() и сразу занести в него информацию о 6 объектах: (1.2, 6.3), (4.0,
    0.7), (7.2, 0.8), (5.3, 3.0), (4.9, 6.6), (9.3, 0.2).
    Вывести список на экран таким образом, чтобы размеры каждого прямоугольника выводились в отдельной строке. Выведите на экран размеры
    прямоугольника, у которого наибольшая площадь. Напишите функцию вывода списка на экран. */
    Rectangle biggest = Rectangle(0., 0.);
    std::list<Rectangle> l = {Rectangle(1.2, 6.3), Rectangle(4.0, 0.7), Rectangle(7.2, 0.8),
                              Rectangle(5.3, 3.0), Rectangle(4.9, 6.6), Rectangle(9.3, 0.2)};
    std::list<Rectangle>::iterator iter;
    for (iter = l.begin(); iter != l.end(); iter++) {
        std::cout << std::setw(5) << (*iter).a << ' ' << std::setw(5) << (*iter).b << "    = " << std::setw(10) << (*iter).a * (*iter).b << '\n';

        if (biggest < *iter) {
            biggest = *iter;
        }
    }
    std::cout << '\n';
    std::cout << std::setw(5) << biggest.a << ' ' << std::setw(5) << biggest.b << "    = " << std::setw(10) << biggest.a * biggest.b << '\n';
}

void mapPrint(std::map<std::string, int> m) {
    for (auto e : m) {
        std::cout << "m[" << e.first << "] = " << e.second << '\n';
    }
}
void Task8() {
    /* 4. Создайте отображение map<string, int> и занесите в него пары "one" - 100, "two" - 200, "three" - 300, ..., "six" - 600.
    Выведите содержимое отображения на экран. Удалить пары с ключами "five" и "six" и снова распечатайте отображение. */
    std::map<std::string, int> m = {};
    std::map<std::string, int>::iterator i;
    m["one"] = 100;
    m["two"] = 200;
    m["three"] = 300;
    m["four"] = 400;
    m["five"] = 500;
    m["six"] = 600;
    mapPrint(m);
    std::cout << '\n';
    m.erase("five");
    m.erase("six");
    mapPrint(m);
}

void printPhoneBook(std::map<std::string, std::string> phoneBook) {
    if (phoneBook.size() == 0) {
        std::cout << "Phone book doesn't contain any records :(" << '\n';
        return;
    }
    std::cout << std::right << std::setw(18) << "Name" << " -- " << std::left << std::setw(18) << "Phone number" << '\n';
    for (auto e : phoneBook) {
        std::cout << std::right << std::setw(18) << e.first << " -- " << std::left << std::setw(18) << e.second << '\n';
    }
}
void Task9() {
    /* 4. Создайте ассоциативный контейнер для хранения имен абонентов и их телефонных номеров. Имена и номера телефонов должны вводиться
    пользователем. После окончания ввода распечатать имена и телефонные номера абонентов в виде строк: имя абонента – его номер. Выполнить поиск
    номера по имени абонента, которое введет пользователь. Удалите найденный номер и имя абонента из отображения. Снова распечатайте отображение. */
    std::map<std::string, std::string> phoneBook = {};
    std::string name, phone;
    while (true) {
        std::cout << "Enter name (or '0' to stop): ";
        std::getline(std::cin, name);
        if (name == "0") {
            break;
        }
        std::cout << "Enter " << name << "'s phone number: ";
        std::getline(std::cin, phone);
        phoneBook[name] = phone;
    }

    std::cout << '\n';
    printPhoneBook(phoneBook);
    std::cout << '\n';

    if (phoneBook.size() == 0) {
        return;
    }

    bool isNumberDeleted = false;
    while (!isNumberDeleted) {
        std::cout << "Enter phone number to be deleted: ";
        std::getline(std::cin, phone);
        for (auto& [key, value] : phoneBook) {
            if (value == phone) {
                phoneBook.erase(key);
                isNumberDeleted = true;
                break;
            }
        }
        if (!isNumberDeleted) {
            std::cout << "No such number has been found. ";
        }
    }

    std::cout << '\n';
    printPhoneBook(phoneBook);
    std::cout << '\n';
}

int main(int argc, char** argv) {
    int selection = 0;
    if (argc == 2) {
        selection = std::atoi(argv[1]);
    } else {
        std::cout << "Choose task (1-9): ";
        std::cin >> selection;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    switch (selection) {
        case 1:
            Task1();
            break;
        case 2:
            Task2();
            break;
        case 3:
            Task3();
            break;
        case 4:
            Task4();
            break;
        case 5:
            Task5();
            break;
        case 6:
            Task6();
            break;
        case 7:
            Task7();
            break;
        case 8:
            Task8();
            break;
        case 9:
            Task9();
            break;
        default:
            return 0;
    }
    return 0;
}
