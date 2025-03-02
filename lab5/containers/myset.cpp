#include "myset.h"

template<>
bool MySet<char*>::operator==(MySet& s) const {
    if (this == &s) {
        return true;
    }
    if (size != s.size) {
        return false;
    }

    for (int i = 0; i < size; ++i) {
        if (std::strcmp(*pdata[i], *s.pdata[i]) == 0) {
            return false;
        }
    }
    return true;
}

template<>
void MySet<char*>::add_element(char* el) {
    MyVector<char*>::add_element(el);
    sort();
}

template<>
void MySet<char*>::delete_element(char* el) {
    int L = 0;
    int R = this->size;

    int m = 0;
    while (R - L > 1) {
        m = L + (R - L) / 2;
        if (std::strcmp(*this->pdata[m], el) > 0) {
            R = m;
        } else {
            L = m;
        }
    }

    if (*this->pdata[m] != el) {
        return;
    }

    this->MyVector<char*>::delete_element(m);
}

template<>
bool MySet<char*>::is_element(char* el) const {
    int L = 0;
    int R = this->size;

    int m = 0;
    while (R - L > 1) {
        m = L + (R - L) / 2;
        if (std::strcmp(*this->pdata[m], el) > 0) {
            R = m;
        } else {
            L = m;
        }
    }

    return *this->pdata[m] == el;
}
