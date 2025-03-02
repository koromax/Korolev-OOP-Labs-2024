#pragma once

#include <iostream>

#include "myvector.h"

template<class INF>
class MySet : public MyVector<INF> {
 public:
    MySet() : MyVector<INF>() {};
    MySet(INF el) : MyVector<INF>(el) {};
    MySet(const MySet& s) : MyVector<INF>(s) {};
    bool operator==(MySet& s) const;
    void add_element(INF el);
    void delete_element(INF el);
    bool is_element(INF el) const;
    MySet& operator+=(const MySet& s);
    MySet& operator-=(const MySet& s);
    MySet& operator*=(const MySet& s);

    template<class T>
    friend std::ostream& operator<<(std::ostream& out, const MySet<T>& s);

    friend MySet operator+(const MySet& s1, const MySet& s2) {
        MySet result = s1;
        result += s2;
        return result;
    }
    friend MySet operator-(const MySet& s1, const MySet& s2) {
        MySet result = s1;
        result -= s2;
        return result;
    }
    friend MySet operator*(const MySet& s1, const MySet& s2) {
        MySet result = s1;
        result *= s2;
        return result;
    }
};

template<>
bool MySet<char*>::operator==(MySet& s) const;
template<>
void MySet<char*>::add_element(char* el);
template<>
void MySet<char*>::delete_element(char* el);
template<>
bool MySet<char*>::is_element(char* el) const;

template<class INF>
bool MySet<INF>::operator==(MySet& s) const {
    if (this == &s) {
        return true;
    }
    if (this->size != s.size) {
        return false;
    }

    for (int i = 0; i < this->size; ++i) {
        if (this->pdata[i] != s.pdata[i]) {
            return false;
        }
    }
    return true;
}

template<class INF>
void MySet<INF>::add_element(INF el) {
    if (this->find(el) != -1) {
        return;
    }
    this->MyVector<INF>::add_element(el);
    this->sort();
}

template<class INF>
void MySet<INF>::delete_element(INF el) {
    int L = 0;
    int R = this->size;

    int m = 0;
    while (R - L > 1) {
        m = L + (R - L) / 2;
        if (*this->pdata[m] > el) {
            R = m;
        } else {
            L = m;
        }
    }

    if (*this->pdata[m] != el) {
        return;
    }

    this->MyVector<INF>::delete_element(m);
}

template<class INF>
bool MySet<INF>::is_element(INF el) const {
    return MyVector<INF>::find(el) != -1;
}

template<class INF>
MySet<INF>& MySet<INF>::operator+=(const MySet& s) {
    for (int i = 0; i < s.size; ++i) {
        this->add_element(s[i]);
    }
    return *this;
}

template<class INF>
MySet<INF>& MySet<INF>::operator-=(const MySet& s) {
    for (int i = 0; i < s.size; ++i) {
        if (this->find(s[i]) != -1) {
            this->delete_element(s[i]);
        }
    }

    return *this;
}

template<class INF>
MySet<INF>& MySet<INF>::operator*=(const MySet& s) {
    int i = 0;
    while (i < this->size) {
        if (s.find(*this->pdata[i]) != -1) {
            ++i;
            continue;
        }
        this->MyVector<INF>::delete_element(i);
    }

    return *this;
}

template<class INF>
std::ostream& operator<<(std::ostream& out, const MySet<INF>& s) {
    for (int i = 0; i < s.size; ++i) {
        out << *s.pdata[i] << " ";
    }
    return out;
}
