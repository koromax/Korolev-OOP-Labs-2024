#include "shop.h"

#include <cstring>
#include <iomanip>

const int kBufferSize = 128;

namespace shop {
shop::shop() = default;

shop::shop(char* name, char* type, double area, bool isLocal) : area(area), isLocal(isLocal) {
    setName(name);
    setType(type);
}

shop::shop(const shop& o) : area(o.area), isLocal(o.isLocal) {
    setName(o.name);
    setType(o.type);
}

shop::~shop() {
    delete[] name;
    delete[] type;
}

char* shop::getName() const {
    return name;
}

char* shop::getType() const {
    return type;
}

double shop::getArea() const {
    return area;
}

bool shop::getLocal() const {
    return isLocal;
}

void shop::setName(char* n) {
    delete[] name;
    name = new char[std::strlen(n) + 1];
    std::memcpy(name, n, std::strlen(n) + 1);
    name[std::strlen(n)] = '\0';
}

void shop::setType(char* t) {
    delete[] type;
    type = new char[std::strlen(t) + 1];
    std::memcpy(type, t, std::strlen(t) + 1);
    type[std::strlen(t)] = '\0';
}

void shop::setArea(double a) {
    area = a;
}

void shop::setLocal(bool l) {
    isLocal = l;
}

void shop::print() {
    std::cout << std::left << "Shop name: " << std::setw(15) << name;
    std::cout << ", Type: " << std::setw(15) << type;
    std::cout << std::right << ", Area: " << std::setw(8) << area;
    std::cout << ", Is Local: " << std::setw(2) << isLocal << '\n';
}

shop& shop::operator=(const shop& p) {
    if (this == &p) {
        return *this;
    }

    this->setName(p.name);
    this->setType(p.type);
    this->area = p.area;
    this->isLocal = p.isLocal;
    return *this;
}

bool operator==(const shop& lhs, const shop& rhs) {
    return (std::strcmp(lhs.name, rhs.name) == 0);
}

bool operator!=(const shop& lhs, const shop& rhs) {
    return !(lhs == rhs);
}

bool operator<(const shop& lhs, const shop& rhs) {
    if (std::strcmp(lhs.name, rhs.name) == 0) {
        if (std::strcmp(lhs.type, rhs.type) == 0) {
            if (lhs.area == rhs.area) {
                return lhs.isLocal < rhs.isLocal;
            }
            return lhs.area < rhs.area;
        }
        return std::strcmp(lhs.type, rhs.type) < 0;
    }
    return std::strcmp(lhs.name, rhs.name) < 0;
}

template<typename stream>
stream& operator>>(stream& in, shop& s) {
    char name[kBufferSize];
    char type[kBufferSize];
    double area;
    bool isLocal;

    in >> name >> type >> area >> isLocal;
    s.setName(name);
    s.setType(type);
    s.setArea(area);
    s.setLocal(isLocal == 1);

    return in;
}

std::ofstream& operator<<(std::ofstream& out, const shop& s) {
    out << s.getName() << ' ' << s.getType() << ' ' << s.getArea() << ' ' << s.getLocal() << '\n';
    return out;
}

template std::istream& operator>>(std::istream& in, shop& s);
template std::ifstream& operator>>(std::ifstream& in, shop& s);
}  // namespace shop
