#pragma once
#include <iostream>
#include <stdexcept>

// Шаблонный класс ListNode (узел односвязного списка)
template<class INF, class FRIEND>
class ListNode  // узел списка
{
 private:
    INF d;                                                               // информационная часть узла
    ListNode* next;                                                      // указатель на следующий узел списка
    ListNode() : next(nullptr) {}                                        // конструктор
    ListNode(INF data, ListNode* nextNode) : d(data), next(nextNode) {}  // конструктор
    friend FRIEND;
};

// Шаблонный класс MyStack на основе односвязного списка.
template<class INF>
class MyStack {
    typedef class ListNode<INF, MyStack<INF>> Node;
    Node* top;

 public:
    MyStack();            // конструктор
    MyStack(MyStack& o);  // конструктор копирования
    ~MyStack();           // освободить динамическую память
    bool empty();         // стек пустой?
    void push(INF n);     // добавить узел в вершину стека
    void pop();           // удалить узел из вершины стека
    INF top_inf();        // считать информацию из вершины стека
    friend std::ostream& operator<<(std::ostream& os, const MyStack<INF>& st) {
        Node* p = st.top;
        while (p->next != nullptr) {
            std::cout << p->d << ' ';
            p = p->next;
        }
        std::cout << p->d;
        return os;
    }
};

template<class INF>
MyStack<INF>::MyStack() : top(nullptr) {
}

template<class INF>
MyStack<INF>::MyStack(MyStack& o) : top(nullptr) {
    MyStack<INF> temp;
    Node* oo = o.top;
    while (oo->next != nullptr) {
        temp.push(oo->d);
        oo = oo->next;
    }
    temp.push(oo->d);

    Node* to = temp.top;
    while (to->next != nullptr) {
        push(to->d);
        to = to->next;
    }
    push(to->d);
}

template<class INF>
MyStack<INF>::~MyStack() {
    while (!empty()) {
        pop();
    };
}

template<class INF>
bool MyStack<INF>::empty() {
    return top == nullptr;
}

template<class INF>
void MyStack<INF>::push(INF n) {
    Node* p = new Node(n, top);
    top = p;
}

template<class INF>
void MyStack<INF>::pop() {
    if (empty()) {
        return;
    }
    Node* p = top;
    top = top->next;
    delete p;
}

template<class INF>
INF MyStack<INF>::top_inf() {
    if (empty()) {
        throw std::runtime_error("Stack is empty");
    }
    return top->d;
}
