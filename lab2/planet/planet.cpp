#include "planet.h"

#include <cstring>

const int kBufferSize = 128;

namespace planet {
planet::planet() = default;

planet::planet(char* n, unsigned int diameter, bool life, unsigned int satelliteCount)
    : diameter(diameter), containsLife(life), satelliteCount(satelliteCount) {
    setName(n);
}

planet::planet(const planet& o) : diameter(o.diameter), containsLife(o.containsLife), satelliteCount(o.satelliteCount) {
    setName(o.name);
}

planet::~planet() {
    delete[] name;
}

char* planet::getName() const {
    return name;
}

unsigned int planet::getDiameter() const {
    return diameter;
}

bool planet::getContainsLife() const {
    return containsLife;
}

unsigned int planet::getSatelliteCount() const {
    return satelliteCount;
}

void planet::setName(char* n) {
    delete[] name;
    name = new char[std::strlen(n) + 1];
    std::memcpy(name, n, std::strlen(n));
    name[std::strlen(n) + 1] = '\0';
}

void planet::setDiameter(unsigned int i) {
    diameter = i;
}

void planet::setLife(bool b) {
    containsLife = b;
}

void planet::setSatelliteCount(unsigned int i) {
    satelliteCount = i;
}

void planet::print() {
    std::cout << std::left << "Name: " << std::setw(10) << name;
    std::cout << ", Diameter: " << std::right << std::setw(6) << diameter;
    std::cout << ", Contains Life: " << std::setw(1) << containsLife;
    std::cout << ", Satellite Count: " << std::setw(2) << satelliteCount << '\n';
}

planet& planet::operator=(const planet& p) {
    if (this == &p) {
        return *this;
    }

    this->setName(p.name);
    this->containsLife = p.containsLife;
    this->diameter = p.diameter;
    this->satelliteCount = p.satelliteCount;
    return *this;
}

bool operator==(const planet& lhs, const planet& rhs) {
    return (std::strcmp(lhs.name, rhs.name) == 0);
}

bool operator!=(const planet& lhs, const planet& rhs) {
    return !(lhs == rhs);
}

bool operator<(const planet& lhs, const planet& rhs) {
    if (std::strcmp(lhs.name, rhs.name) == 0) {
        if (lhs.diameter == rhs.diameter) {
            if (lhs.containsLife == rhs.containsLife) {
                return lhs.satelliteCount < rhs.satelliteCount;
            }
            return lhs.containsLife < rhs.containsLife;
        }
        return lhs.diameter < rhs.diameter;
    }
    return std::strcmp(lhs.name, rhs.name) < 0;
}

template<typename stream>
stream& operator>>(stream& in, planet& p) {
    char name[kBufferSize];
    unsigned int diameter = 0;
    bool life = false;
    unsigned int satelliteCount = 0;

    in >> name >> diameter >> life >> satelliteCount;
    p.setName(name);
    p.setDiameter(diameter);
    p.setLife(life == 1);
    p.setSatelliteCount(satelliteCount);

    return in;
}

std::ofstream& operator<<(std::ofstream& out, const planet& p) {
    out << p.getName() << ' ' << p.getDiameter() << ' ' << p.getContainsLife() << ' ' << p.getSatelliteCount() << '\n';
    return out;
}

template std::istream& operator>>(std::istream& in, planet& p);
template std::ifstream& operator>>(std::ifstream& in, planet& p);
}  // namespace planet
