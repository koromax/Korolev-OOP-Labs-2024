#include "myvector.h"
#include <cstring>

template<>
void MyVector<char*>::resize() {
    if (size >= capacity) {
        capacity *= 2;
    } else if (size < capacity / 4) {
        capacity /= 2;
    } else {
        return;
    }

    char*** temp = new char**[capacity];
    for (int i = 0; i < size; ++i) {
        temp[i] = new char*;
        *temp[i] = new char[std::strlen(*pdata[i]) + 1];
        std::strcpy(*temp[i], *pdata[i]);
        delete[] pdata[i];
    }
    delete[] pdata;
    pdata = temp;
}

template<>
MyVector<char*>::MyVector(char* el) : size(1), capacity(defaultCapacity) {
    pdata[0] = new char*;
    *pdata[0] = new char[std::strlen(el) + 1];
    std::strcpy(*pdata[0], el);
}

template<>
MyVector<char*>::MyVector(const MyVector& v) : size(v.size), capacity(v.capacity) {
    for (int i = 0; i < size; ++i) {
        pdata[i] = new char*;
    }
    for (int i = 0; i < size; ++i) {
        *pdata[i] = new char[std::strlen(*v.pdata[i]) + 1];
        std::strcpy(*pdata[0], *v.pdata[i]);
    }
}

template<>
void MyVector<char*>::add_element(char* el) {
    if (size >= capacity) {
        resize();
    }
    pdata[size] = new char*;
    *pdata[size] = new char[std::strlen(el) + 1];
    std::strcpy(*pdata[size], el);
    size++;
}

template<>
void MyVector<char*>::sort() {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (std::strcmp(*pdata[i], *pdata[j]) > 0) {
                char** temp = pdata[i];
                pdata[i] = pdata[j];
                pdata[j] = temp;
            }
        }
    }
}

template class MyVector<char*>;
