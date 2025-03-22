#include "Polynomial.h"

Term::Term(const char* s) {
    const int kBufferSize = 128;
    char buffer[kBufferSize];
    std::strncpy(buffer, s, kBufferSize);
    buffer[kBufferSize - 1] = '\0';

    /*

    All possible forms of a Term

    REPLACE '+' WITH
          = '1' IF k = 1 ("+x^p" --> "1x^p")
          = '0' IF k != 1 ("+kx^p" --> "0kx^p")

    NO NEGATIVE EXPONENT

    '-' --> remove character and *(-1) the coefficient at the end

    k            = kx^0
    x = x^p = kx = 1x^1
        x^p      = 1x^p
              kx = kx^1
                   kx^p

    */

    bool isNegative = false;
    if (std::strlen(buffer) > 1 && (buffer[0] == '+' || buffer[0] == '-')) {
        if (buffer[0] == '-') {
            isNegative = true;
        }

        if (buffer[1] == 'x') {
            buffer[0] = '1';
        } else {
            buffer[0] = '0';
        }
    }

    int c = 0;
    int d = 0;

    if (std::strcmp(s, "x") == 0) {
        coefficient = 1;
        degree = 1;
        return;
    }

    int parsed = std::sscanf(buffer, "%dx^%d", &c, &d);
    if (parsed == 2) {
        coefficient = c;
        degree = d;
    } else {
        int parsed = std::sscanf(buffer, "x^%d", &d);
        if (parsed == 1) {
            coefficient = 1;
            degree = d;
        } else {
            int parsed = std::sscanf(buffer, "%d", &c);
            if (parsed == 1) {
                coefficient = c;
                if (std::find(buffer, buffer + kBufferSize, 'x') != buffer + kBufferSize) {
                    degree = 1;
                } else {
                    degree = 0;
                }
            } else {
                std::cerr << "Invalid term format" << std::endl;
            }
        }
    }

    if (isNegative && coefficient != 0) {
        coefficient *= -1;
    }
}

Term& Term::operator+=(const Term& o) {
    if (this->degree != o.degree) {
        std::cout << "the dergees of terms differ." << '\n';
        return *this;
    }
    coefficient += o.coefficient;
    return *this;
}

Term& Term::operator*=(const Term& o) {
    this->degree += o.degree;
    this->coefficient *= o.coefficient;
    return *this;
}

Term operator+(const Term& lhs, const Term& rhs) {
    Term result = lhs;
    result += rhs;
    return result;
}

Term operator*(const Term& lhs, const Term& rhs) {
    Term result = lhs;
    result *= rhs;
    return result;
}

std::istream& operator>>(std::istream& is, Term& t) {
    const int kBufferSize = 128;
    char buffer[kBufferSize];
    is.getline(buffer, kBufferSize);

    t = Term(buffer);

    if (is.fail()) {
        is.setstate(std::ios::failbit);
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const Term& t) {
    if (t.coefficient == 0) {
        std::cout << 0;
        return os;
    }

    if (t.coefficient < 0) {
        std::cout << '-';
    }

    if (std::abs(t.coefficient) != 1 || t.degree == 0) {
        os << std::abs(t.coefficient);
    }

    if (t.degree == 0) {
        return os;
    }

    os << 'x';

    if (t.degree != 1) {
        os << '^' << t.degree;
    }

    return os;
}

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs) {
    Polynomial result = lhs;
    result += rhs;
    return result;
}

Polynomial operator*(const Polynomial& lhs, const Polynomial& rhs) {
    Polynomial result = lhs;
    result *= rhs;
    return result;
}

std::istream& operator>>(std::istream& is, Polynomial& p) {
    const int kBufferSize = 256;
    char buffer[kBufferSize];
    is.getline(buffer, kBufferSize);

    p = Polynomial(buffer);

    if (is.fail()) {
        is.setstate(std::ios::failbit);
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
    if (p.degree == 0 && p[0].GetCoefficient() == 0) {
        os << 0;
        return os;
    }

    bool firstTerm = true;
    int i = !p.order_ ? p.degree : 0;
    while (i >= 0 && i <= p.degree) {
        Term term = p[i];

        if (term.GetCoefficient() == 0) {
            !p.order_ ? i-- : i++;
            continue;
        }

        if (!firstTerm) {
            if (term.GetCoefficient() > 0) {
                os << " + ";
            } else {
                os << " - ";
            }
        } else if (term.GetCoefficient() < 0) {
            os << "-";
        }

        if (std::abs(term.GetCoefficient()) != 1 || term.GetDegree() == 0) {
            os << std::abs(term.GetCoefficient());
        }

        if (term.GetDegree() != 0) {
            os << 'x';
            if (term.GetDegree() != 1) {
                os << '^' << term.GetDegree();
            }
        }

        firstTerm = false;
        !p.order_ ? i-- : i++;
    }

    return os;
}

Polynomial::Polynomial(const char* s) {
    const int kBufferSize = 256;
    char buffer[kBufferSize];
    std::strncpy(buffer, s, kBufferSize);
    buffer[kBufferSize - 1] = '\0';

    // removing all spaces
    int i = 0;
    int j = 0;
    int spaceCount = 0;
    while (i < kBufferSize && buffer[i] != '\0') {
        if (std::strlen(buffer) - spaceCount == i) {
            buffer[i] = '\0';
            break;
        }

        if (buffer[i] == ' ') {
            spaceCount++;
            j = i;
            while (j < kBufferSize && buffer[j + 1] != '\0') {
                std::swap(buffer[j], buffer[j + 1]);
                ++j;
            }
        } else {
            ++i;
        }
    }

    int bufbufLength = 2 * std::strlen(buffer);
    char bufbuf[bufbufLength];
    std::strncpy(bufbuf, buffer, bufbufLength);

    // adding a space before '+' and '-'
    i = 1;
    j = bufbufLength - 1;
    while (i < bufbufLength && bufbuf[i] != '\0') {
        if (bufbuf[i] == '+' || bufbuf[i] == '-') {
            j = bufbufLength - 1;
            while (j >= i) {
                bufbuf[j] = bufbuf[j - 1];
                j--;
            }
            bufbuf[i] = ' ';
            i++;
        }
        i++;
    }

    char delimiters[2] = " ";
    char* token = std::strtok(bufbuf, delimiters);
    while (token != NULL) {
        this->AddTerm(Term(token));
        token = std::strtok(NULL, delimiters);
    }
}

void Polynomial::AddTerm(Term t) {
    while (terms.find(t) != -1) {
        t += terms[terms.find(t)];
        terms.delete_element(terms.find(t));
        size--;
    }
    this->terms.add_element(t);
    size++;
    if (t.GetDegree() > this->degree && t.GetCoefficient() != 0) {
        this->degree = t.GetDegree();
    } else if ((*this)[this->degree].GetCoefficient() == 0) {
        while (this->degree > 0 && (*this)[this->degree].GetCoefficient() != 0) {
            this->degree--;
        }
    }
    this->terms.sort();
}

void Polynomial::DeleteTerm(Term t) {
    while (this->size > 0 && terms.find(t) != -1) {
        terms.delete_element(terms.find(t));
        size--;
    }
}

void Polynomial::Clear() {
    while (this->size > 0) {
        terms.delete_element(0);
        size--;
    }
    this->degree = 0;
}

Polynomial& Polynomial::operator+=(const Polynomial& o) {
    for (int i = 0; i <= o.degree; ++i) {
        this->AddTerm(o[i]);
    }
    return *this;
}

Polynomial& Polynomial::operator*=(const Polynomial& o) {
    Polynomial temp = *this;
    this->Clear();
    for (int i = 0; i <= temp.degree; ++i) {
        for (int j = 0; j <= o.degree; ++j) {
            this->AddTerm(temp[i] * o[j]);
        }
    }

    return *this;
}
