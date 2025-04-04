#pragma once

#include <fstream>
#include <iostream>

namespace shop {
class shop {
 public:
    shop();
    shop(char* name, char* type, double area, bool isLocal);
    shop(const shop& o);
    ~shop();

    char* getName() const;
    char* getType() const;
    double getArea() const;
    bool getLocal() const;

    void setName(char* n);
    void setType(char* t);
    void setArea(double a);
    void setLocal(bool l);

    void print();

    shop& operator=(const shop& p);
    friend bool operator==(const shop& lhs, const shop& rhs);
    friend bool operator!=(const shop& lhs, const shop& rhs);
    friend bool operator<(const shop& lhs, const shop& rhs);

 private:
    char* name = nullptr;
    char* type = nullptr;
    double area = .0;
    bool isLocal = true;
};

template<typename stream>
stream& operator>>(stream& in, shop& s);
std::ofstream& operator<<(std::ofstream& out, const shop& s);
}  // namespace shop
