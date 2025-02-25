#include "fraction.h"
#include <cstring>
#include <iostream>
#include <numeric>

namespace fraction {

fraction::fraction() {
}

fraction::fraction(int n, int d) : numerator(n), denominator(d) {
    if (d == 0 && n != 0) {
        std::cout << "Denominator cannot be zero. Assuming 1." << '\n';
        denominator = 1;
    }

    normalize();
}

fraction::fraction(int w) : whole(w) {
    normalize();
}

fraction::fraction(int w, int n, int d) : whole(w), numerator(n), denominator(d) {
    if (d == 0 && n != 0) {
        std::cout << "Denominator cannot be zero. Assuming 1." << '\n';
        denominator = 1;
    }

    normalize();
}

fraction::fraction(double value) {
    isNegative = value < 0;
    value = std::abs(value);

    whole = static_cast<int>(value);
    double fractionalPart = value - whole;

    const int precision = 1e7;
    numerator = static_cast<int>(fractionalPart * precision);
    denominator = precision;

    normalize();
}

fraction::fraction(const char* s) {
    if (s == nullptr) {
        std::cerr << "Invalid fraction format: null string" << std::endl;
        return;
    }

    const int kBufferSize = 128;
    char buffer[kBufferSize];
    std::strncpy(buffer, s, kBufferSize);
    buffer[kBufferSize - 1] = '\0';

    int w = 0;
    int n = 0;
    int d = 1;

    int parsed = std::sscanf(buffer, "%d %d/%d", &w, &n, &d);
    if (parsed == 3) {
        SetWhole(w);
        SetDenominator(d);
        SetNumerator(n);
    } else {
        parsed = std::sscanf(buffer, "%d/%d", &n, &d);
        if (parsed == 2) {
            SetWhole(0);
            SetDenominator(d);
            SetNumerator(n);
        } else {
            parsed = std::sscanf(buffer, "%d", &w);
            if (parsed == 1) {
                SetWhole(w);
                SetDenominator(1);
                SetNumerator(0);
            } else {
                std::cerr << "Invalid fraction format" << std::endl;
            }
        }
    }

    normalize();
}

fraction::fraction(const fraction& other)
    : whole(other.whole), numerator(other.numerator), denominator(other.denominator), isNegative(other.isNegative) {
    normalize();
}

fraction::~fraction() {
}

void fraction::SetNumerator(int n) {
    numerator = n;
}

void fraction::SetDenominator(int d) {
    if (d == 0 && numerator != 0) {
        std::cout << "Denominator cannot be zero." << '\n';
        return;
    }

    denominator = d;
}

void fraction::SetWhole(int w) {
    whole = w;
}

int fraction::GetNumerator() const {
    return numerator;
}

int fraction::GetDenominator() const {
    return denominator;
}

int fraction::GetWhole() const {
    return whole;
}

bool fraction::GetNegative() const {
    return isNegative;
}

fraction fraction::operator=(const fraction& other) {
    if (this == &other) {
        return *this;
    }

    this->numerator = other.numerator;
    this->denominator = other.denominator;
    this->whole = other.whole;
    this->isNegative = other.isNegative;
    return *this;
}

fraction& fraction::operator+=(const fraction& other) {
    if (this->isNegative != other.isNegative) {
        this->isNegative = !this->isNegative;
        *this -= other;
        this->isNegative = !this->isNegative;
        return *this;
    }

    if (this->denominator == other.denominator) {
        this->numerator += other.numerator;
        this->whole += other.whole;
        this->normalize();
        return *this;
    }

    this->numerator = other.denominator * (this->whole * this->denominator + this->numerator) +
                      this->denominator * (other.whole * other.denominator + other.numerator);
    this->denominator *= other.denominator;
    this->whole = 0;

    this->normalize();
    return *this;
}

fraction& fraction::operator-=(const fraction& other) {
    if (this->isNegative != other.isNegative) {
        this->isNegative = !this->isNegative;
        *this += other;
        this->isNegative = !this->isNegative;
        return *this;
    }

    if (this->denominator == other.denominator) {
        this->numerator -= other.numerator;
        this->whole -= other.whole;
        this->normalize();
        return *this;
    }

    this->numerator = other.denominator * (this->whole * this->denominator + this->numerator) -
                      this->denominator * (other.whole * other.denominator + other.numerator);
    this->denominator *= other.denominator;
    this->whole = 0;

    this->normalize();
    return *this;
}

fraction& fraction::operator*=(const fraction& other) {
    if (this->isNegative == other.isNegative) {
        this->isNegative = false;
    } else {
        this->isNegative = true;
    }

    /*
          b       e     (a * c + b) * (d * f + e)
        a -  *  d -  =  -------------------------
          c       f               c * f
    */

    this->numerator = (this->whole * this->denominator + this->numerator) * (other.whole * other.denominator + other.numerator);
    this->denominator *= other.denominator;
    this->whole = 0;

    this->normalize();
    return *this;
}

fraction& fraction::operator/=(const fraction& other) {
    fraction otherCopy = other;
    otherCopy.reciprocate();
    return *this *= otherCopy;
}

fraction operator+(fraction lhs, const fraction& rhs) {
    return lhs += rhs;
}

fraction operator-(fraction lhs, const fraction& rhs) {
    return lhs -= rhs;
}

fraction operator*(fraction lhs, const fraction& rhs) {
    return lhs *= rhs;
}

fraction operator/(fraction lhs, const fraction& rhs) {
    return lhs /= rhs;
}

std::istream& operator>>(std::istream& is, fraction& fr) {
    const int kBufferSize = 128;
    char buffer[kBufferSize];
    is.getline(buffer, kBufferSize);

    fr = fraction(buffer);

    if (is.fail()) {
        is.setstate(std::ios::failbit);
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const fraction& fr) {
    if (fr.GetNegative()) {
        os << '-';
    }

    if (fr.GetWhole() != 0) {
        os << fr.GetWhole();
        if (fr.GetNumerator() != 0) {
            os << ' ';
        }
    }

    if (fr.GetNumerator() != 0) {
        os << fr.GetNumerator() << '/' << fr.GetDenominator();
    } else if (fr.GetWhole() == 0) {
        os << 0;
    }

    return os;
}

void fraction::reciprocate() {
    if (whole == 0 && numerator == 0) {
        std::cout << "Cannot reciprocate zero" << '\n';
        return;
    }
    this->improperForm();

    std::swap(numerator, denominator);
    normalize();
}

double fraction::toDouble() const {
    return (whole * denominator + numerator) / static_cast<double>(denominator);
}

fraction& fraction::improperForm() {
    this->numerator += this->whole * this->denominator;
    this->whole = 0;
    return *this;
}

fraction& fraction::normalize() {
    if (whole < 0) {
        isNegative = !isNegative;
        whole = std::abs(whole);
    }

    if (numerator < 0) {
        isNegative = !isNegative;
        numerator = std::abs(numerator);
    }

    if (denominator < 0) {
        isNegative = !isNegative;
        denominator = std::abs(denominator);
    }

    while (numerator >= denominator) {
        numerator -= denominator;
        whole++;
    }

    if (whole == 0 && numerator == 0) {
        isNegative = !isNegative;
    }

    if (numerator == 0) {
        denominator = 1;
        return *this;
    }

    int d = std::gcd(numerator, denominator);
    if (d == 0) {
        std::cout << "fraction::normalize() int d = std::gcd(" << numerator << ", " << denominator << ") = " << d << '\n';
        return *this;
    }

    numerator /= d;
    denominator /= d;

    return *this;
}
}  // namespace fraction
