#pragma once

#include <cmath>
#include <cstring>
#include <iostream>
#include <stdexcept>

const int defaultCapacity = 1;

template<class INF>
class MyVector {
 protected:
    int capacity = defaultCapacity;
    int size = 0;
    INF** pdata;
    void resize();

 public:
    MyVector();
    MyVector(INF el);
    MyVector(const MyVector& v);
    ~MyVector();
    void add_element(INF el);
    bool delete_element(int i);
    INF operator[](int i) const;
    void sort();
    int get_size() const { return size; }
    int get_capacity() const { return capacity; }
    int find(INF el) const;
    MyVector& operator=(const MyVector& v);

    template<class T>
    friend std::ostream& operator<<(std::ostream& out, const MyVector<T>& v);
};

template<>
void MyVector<char*>::resize();

template<class INF>
void MyVector<INF>::resize() {
    if (size >= capacity) {
        capacity *= 2;
    } else if (size < capacity / 4) {
        capacity /= 2;
    } else {
        return;
    }

    INF** temp = new INF*[capacity];
    for (int i = 0; i < size; ++i) {
        temp[i] = pdata[i];
    }
    delete[] pdata;
    pdata = temp;
}

template<>
MyVector<char*>::MyVector(char* el);
template<>
MyVector<char*>::MyVector(const MyVector& v);
template<>
void MyVector<char*>::add_element(char* el);
template<>
void MyVector<char*>::sort();

template<class INF>
MyVector<INF>::MyVector() : size(0), capacity(defaultCapacity) {
    pdata = new INF*[capacity];
}

template<class INF>
MyVector<INF>::MyVector(INF el) : size(1), capacity(defaultCapacity) {
    pdata = new INF*[capacity];
    pdata[0] = new INF(el);
}

template<class INF>
MyVector<INF>::MyVector(const MyVector& v) : size(v.size), capacity(v.capacity) {
    pdata = new INF*[capacity];
    for (int i = 0; i < size; ++i) {
        pdata[i] = new INF(*v.pdata[i]);
    }
}

template<class INF>
MyVector<INF>::~MyVector() {
    for (int i = 0; i < size; ++i) {
        delete pdata[i];
    }
    delete[] pdata;
}

template<class INF>
void MyVector<INF>::add_element(INF el) {
    if (size >= capacity) {
        resize();
    }
    pdata[size++] = new INF(el);
}

template<class INF>
bool MyVector<INF>::delete_element(int i) {
    if (i < 0 || i >= size) {
        return false;
    }

    delete pdata[i];
    for (int j = i; j < size - 1; ++j) {
        pdata[j] = pdata[j + 1];
    }
    --size;
    return true;
}

template<class INF>
INF MyVector<INF>::operator[](int i) const {
    if (i < 0 || i >= size) {
        throw std::runtime_error("index is out of range");
    }
    return *pdata[i];
}

template<class INF>
void MyVector<INF>::sort() {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (*pdata[i] > *pdata[j]) {
                INF* temp = pdata[i];
                pdata[i] = pdata[j];
                pdata[j] = temp;
            }
        }
    }
}

template<class INF>
int MyVector<INF>::find(INF el) const {
    for (int i = 0; i < size; ++i) {
        if (*pdata[i] == el) {
            return i;
        }
    }
    return -1;
}

template<class INF>
MyVector<INF>& MyVector<INF>::operator=(const MyVector<INF>& v) {
    if (this == &v) {
        return *this;
    }

    for (int i = 0; i < size; ++i) {
        delete pdata[i];
    }
    delete[] pdata;

    size = v.size;
    capacity = v.capacity;
    pdata = new INF*[capacity];
    for (int i = 0; i < size; ++i) {
        pdata[i] = new INF(*v.pdata[i]);
    }

    return *this;
}

template<class INF>
std::ostream& operator<<(std::ostream& out, const MyVector<INF>& v) {
    for (int i = 0; i < v.size; ++i) {
        out << *v.pdata[i] << " ";
    }
    return out;
}
