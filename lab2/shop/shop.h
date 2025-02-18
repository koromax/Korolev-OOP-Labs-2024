#pragma once

#include <fstream>
#include <iostream>

namespace shop {
class shop {
 public:
    shop();
    shop(char* name, char* type, double area, bool isLocal);
    ~shop();

    char* getName();
    char* getType();
    double getArea();
    bool getLocal();

    void setName(char* n);
    void setType(char* t);
    void setArea(double a);
    void setLocal(bool l);

    void print();

    friend bool operator==(const shop& lhs, const shop& rhs);
    friend bool operator!=(const shop& lhs, const shop& rhs);
    friend bool operator<(const shop& lhs, const shop& rhs);
    shop& operator=(const shop& p);

 private:
    char* name = nullptr;
    char* type = nullptr;
    double area = .0;
    bool isLocal = true;
};

std::istream& operator>>(std::istream& in, shop& p);

std::ifstream& operator>>(std::ifstream& in, shop& p);
std::ofstream& operator<<(std::ofstream& out, shop& p);
}  // namespace shop
