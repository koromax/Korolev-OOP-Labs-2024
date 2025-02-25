#include "shop.h"

#include <cstring>

const int kBufferSize = 128;

namespace shop {
shop::shop() : name(), type(), area(), isLocal() {
}

shop::shop(char* name, char* type, double area, bool isLocal) : area(area), isLocal(isLocal) {
    setName(name);
    setType(type);
}

shop::~shop() {
    // delete[] name;
}

char* shop::getName() {
    return name;
}

char* shop::getType() {
    return type;
}

double shop::getArea() {
    return area;
}

bool shop::getLocal() {
    return isLocal;
}

void shop::setName(char* n) {
    delete[] name;
    name = new char[std::strlen(n) + 1];
    std::memcpy(name, n, std::strlen(n));
    name[std::strlen(n)] = '\0';
}

void shop::setType(char* t) {
    delete[] type;
    type = new char[std::strlen(t) + 1];
    std::memcpy(type, t, std::strlen(t));
    name[std::strlen(t)] = '\0';
}

void shop::setArea(double a) {
    area = a;
}

void shop::setLocal(bool l) {
    isLocal = l;
}

void shop::print() {
    std::cout << "Shop name: " << name << ", Type: " << type << ", Area: " << area << ", Is Local: " << isLocal << '\n';
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

std::istream& operator>>(std::istream& in, shop& p) {
    char name[kBufferSize];
    char type[kBufferSize];
    double area;
    bool isLocal;

    in >> name >> type >> area >> isLocal;
    p.setName(name);
    p.setType(type);
    p.setArea(area);
    p.setLocal(isLocal == 1);

    return in;
}

std::ifstream& operator>>(std::ifstream& in, shop& p) {
    char name[kBufferSize];
    char type[kBufferSize];
    double area;
    bool isLocal;

    in >> name >> type >> area >> isLocal;
    p.setName(name);
    p.setType(type);
    p.setArea(area);
    p.setLocal(isLocal == 1);

    return in;
}

std::ofstream& operator<<(std::ofstream& out, shop& p) {
    out << p.getName() << ' ' << p.getType() << ' ' << p.getArea() << ' ' << p.getLocal() << '\n';
    return out;
}

}  // namespace shop
