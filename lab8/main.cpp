#include <algorithm>
#include <cstring>
#include <iostream>

void Task1() {
    /* 14. Пользователь вводит текст. Вывести на экран номера позиций в которых встречается символ @. */
    std::string s;
    std::cin >> s;
    auto i = std::find(s.begin(), s.end(), '@');
    while (i != s.end()) {
        std::cout << std::distance(s.begin(), i) << ' ';
    }
    std::cout << '\n';
}

int main() {
    setlocale(LC_ALL, "Russian");
    Task1();
    return 0;
}
