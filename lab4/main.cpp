#include <iostream>

#include "MyStack/MyStack.h"

bool IsPrime(int n) {
    if (n < 2) {
        return false;
    }
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

void Multipliers(int n, MyStack<int>& stack, bool reversed = false) {
    int d = n;
    if (reversed) {
        d = 2;
    }

    while (n != 1 && (d > 1 && d <= n)) {
        if (!IsPrime(d)) {
            reversed ? d++ : d--;
            continue;
        }

        while (n % d == 0) {
            stack.push(d);
            n /= d;
        }
        reversed ? d++ : d--;
    }
};

void task() {
    MyStack<int> st;
    int n = 11 * 13 * 7 * 5 * 2 * 10 * 37;

    Multipliers(n, st);
    std::cout << n << " = ";
    while (!st.empty()) {
        std::cout << st.top_inf();
        st.pop();
        if (!st.empty())
            std::cout << " * ";
    }
    std::cout << "\n";

    Multipliers(n, st, true);
    std::cout << n << " = ";
    while (!st.empty()) {
        std::cout << st.top_inf();
        st.pop();
        if (!st.empty())
            std::cout << " * ";
    }
    std::cout << "\n";
}

void chars() {
    MyStack<const char*> st;
    st.push("afdaj");
    st.push("d");
    st.push("f");
    st.push("2");
    MyStack<const char*> st1 = st;
    st.push(".");
    st.push("!");
    std::cout << st << '\n';
    std::cout << st1 << '\n';
}

int main() {
    chars();
}
