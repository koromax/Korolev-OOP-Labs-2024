#include "myvector.h"
#include <cstring>

template<>
const int MyVector<char*>::compareItems(char* i, char* j) const {
    return std::strcmp(i, j);
}

template<>
MyVector<char*>::MyVector(char* el) : size(1), capacity(defaultCapacity) {
    pdata = new char**[capacity];
    pdata[0] = new char*;
    *pdata[0] = new char[std::strlen(el)];
    std::memcpy(*pdata[0], el, std::strlen(el));
    pdata[0][0][std::strlen(el)] = '\0';
}

template<>
MyVector<char*>::MyVector(const MyVector& v) : size(v.size), capacity(v.capacity) {
    pdata = new char**[capacity];
    for (int i = 0; i < size; ++i) {
        pdata[i] = new char*;
        *pdata[i] = new char[std::strlen(*v.pdata[i]) + 1];
        std::memcpy(*pdata[i], *v.pdata[i], std::strlen(*v.pdata[i]));
        pdata[i][0][std::strlen(*v.pdata[i])] = '\0';
    }
}

template<>
MyVector<char*>::~MyVector() {
    for (int i = 0; i < size; ++i) {
        delete[] *pdata[i];
        delete pdata[i];
    }
    delete[] pdata;
}

template<>
void MyVector<char*>::add_element(char* el) {
    if (size >= capacity) {
        resize();
    }
    pdata[size] = new char*;
    *pdata[size] = new char[std::strlen(el) + 1];
    std::memcpy(*pdata[size], el, std::strlen(el));
    pdata[size][0][std::strlen(el)] = '\0';
    size++;
}
