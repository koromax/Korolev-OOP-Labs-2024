#pragma once

#include <cstring>
#include <iostream>

#include "../lib/MyVector.h"

class Term {
 private:
    int coefficient = 0;
    int degree = 0;

    void SetCoefficient(const int c) { coefficient = c; }
    void SetDegree(const int d) { degree = d; }

 public:
    Term(int c = 0, int d = 0) : coefficient(c), degree(d) {};
    Term(const Term& o) : coefficient(o.coefficient), degree(o.degree) {};
    Term(const char* s);

    const int GetCoeficcient() const { return coefficient; }
    const int GetDegree() const { return degree; }

    Term& operator+=(const Term& o);
    Term& operator*=(const Term& o);
    friend Term operator+(const Term& lhs, const Term& rhs);
    friend Term operator*(const Term& lhs, const Term& rhs);
    friend bool operator<(const Term& lhs, const Term& rhs) { return lhs.degree < rhs.degree; }
    friend bool operator>(const Term& lhs, const Term& rhs) { return lhs.degree > rhs.degree; }
    friend bool operator==(const Term& lhs, const Term& rhs) { return lhs.degree == rhs.degree; }

    friend std::istream& operator>>(std::istream& is, Term& t);
    friend std::ostream& operator<<(std::ostream& os, const Term& t);
};

class Polynomial {
 private:
    MyVector<Term> terms;
    int size = 0;
    int degree = 0;
    bool order_ = false;

 public:
    Polynomial() = default;
    Polynomial(const int i) : size(1), degree(1) { Term* terms = new Term(i); }
    Polynomial(const Term t) : size(1), degree(t.GetDegree()) { Term* terms = new Term(t); }
    Polynomial(const char* s);
    Polynomial(const Polynomial& p) : size(p.size), degree(p.degree), order_(p.order_), terms(p.terms) {}

    void SetOrder(const bool b) { order_ = b; }

    void AddTerm(Term t);
    void DeleteTerm(Term t);
    void Clear();

    Term operator[](int degree) const { return terms.find(Term(1, degree)) != -1 ? terms[terms.find(Term(1, degree))] : Term(0, degree); }

    Polynomial& operator+=(const Polynomial& o);
    Polynomial& operator*=(const Polynomial& o);
    friend Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);
    friend Polynomial operator*(const Polynomial& lhs, const Polynomial& rhs);

    friend std::istream& operator>>(std::istream& is, Polynomial& p);
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& p);
};
