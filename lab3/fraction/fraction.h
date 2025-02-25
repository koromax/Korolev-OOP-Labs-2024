#pragma once
#include <cstring>
#include <iostream>

namespace fraction {
class fraction {
 private:
    int whole = 0;
    int numerator = 0;
    int denominator = 1;
    bool isNegative = false;

 public:
    fraction();
    fraction(int n, int d);
    fraction(int w);
    fraction(int w, int n, int d);
    fraction(double value);
    fraction(const char* s);

    void SetNumerator(int n);
    void SetDenominator(int d);
    void SetWhole(int w);

    int GetNumerator() const;
    int GetDenominator() const;
    int GetWhole() const;
    bool GetNegative() const;

    fraction operator=(const fraction& other);

    fraction& operator+=(const fraction& other);
    fraction& operator-=(const fraction& other);
    fraction& operator*=(const fraction& other);
    fraction& operator/=(const fraction& other);

    friend fraction operator+(fraction lhs, const fraction& rhs);
    friend fraction operator-(fraction lhs, const fraction& rhs);
    friend fraction operator*(fraction lhs, const fraction& rhs);
    friend fraction operator/(fraction lhs, const fraction& rhs);

    void reciprocate();

    double toDouble() const;
    fraction improperForm();
    fraction normalize();
};

std::istream& operator>>(std::istream& is, fraction& fr);
std::ostream& operator<<(std::ostream& os, const fraction& fr);

}  // namespace fraction
