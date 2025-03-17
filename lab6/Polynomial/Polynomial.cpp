#include "Polynomial.h"

Term::Term(const char* s) {
    const int kBufferSize = 128;
    char buffer[kBufferSize];
    std::strncpy(buffer, s, kBufferSize);
    buffer[kBufferSize - 1] = '\0';

    if (buffer[0] == '+' && buffer[1] != 'x') {
        buffer[0] = '0';
    } else if (buffer[0] == '+' && buffer[1] == 'x') {
        buffer[0] = '1';
    }
    int c = 0;
    int d = 0;

    int parsed = std::sscanf(buffer, "%dx^%d", &c, &d);
    if (parsed == 2) {
        SetCoefficient(c);
        SetDegree(d);
    } else {
        parsed = std::sscanf(buffer, "%dx", &c);
        if (parsed == 1 && std::find(buffer, buffer + kBufferSize, 'x') != buffer + kBufferSize) {
            SetCoefficient(c);
            SetDegree(1);
        } else {
            parsed = std::sscanf(buffer, "-x^%d", &d);
            if (parsed == 1) {
                SetCoefficient(-1);
                SetDegree(d);
            } else {
                parsed = std::sscanf(buffer, "x^%d", &d);
                if (parsed == 1) {
                    SetCoefficient(1);
                    SetDegree(d);
                } else {
                    parsed = std::sscanf(buffer, "%d", &c);
                    if (parsed == 1) {
                        SetCoefficient(c);
                        SetDegree(0);
                    } else {
                        if (std::strcmp(s, "-x") == 0) {
                            SetCoefficient(-1);
                            SetDegree(1);
                        } else if (std::strcmp(s, "x") == 0) {
                            SetCoefficient(1);
                            SetDegree(1);
                        } else {
                            std::cerr << "Invalid term format" << std::endl;
                        }
                    }
                }
            }
        }
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
        return os;
    }

    if (t.coefficient != 1) {
        os << t.coefficient;
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
    if (p.size == 0) {
        os << 0;
        return os;
    }

    bool firstTerm = true;
    int i = !p.order_ ? p.degree : 0;
    while (i >= 0 && i <= p.degree) {
        Term term = p[i];

        if (term.GetCoeficcient() == 0) {
            !p.order_ ? i-- : i++;
            continue;
        }

        if (!firstTerm) {
            if (term.GetCoeficcient() > 0) {
                os << " + ";
            } else {
                os << " - ";
            }
        } else if (term.GetCoeficcient() < 0) {
            os << "-";
        }

        if (std::abs(term.GetCoeficcient()) != 1 || term.GetDegree() == 0) {
            os << std::abs(term.GetCoeficcient());
        }

        if (term.GetDegree() > 0) {
            os << 'x';
            if (term.GetDegree() > 1) {
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

    // std::cout << buffer << '\n';

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

    // std::cout << buffer << '\n';

    int bufbufLength = 2 * std::strlen(buffer);
    char bufbuf[bufbufLength];
    std::strncpy(bufbuf, buffer, bufbufLength);
    // std::cout << bufbuf << '\n';

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

    // std::cout << bufbuf << '\n';

    char delimiters[2] = " ";
    char* token = std::strtok(bufbuf, delimiters);
    while (token != NULL) {
        // std::cout << "token:" << token << "|\n";
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
    if (t.GetDegree() > this->degree) {
        this->degree = t.GetDegree();
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
            // std::cout << temp[i] << " * " << o[j] << " = " << temp[i] * o[j] << '\n';
            this->AddTerm(temp[i] * o[j]);
        }
    }

    return *this;
}
