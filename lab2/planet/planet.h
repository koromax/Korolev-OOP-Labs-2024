#pragma once

#include <fstream>
#include <iostream>

namespace planet {
class planet {
 public:
    planet();
    planet(char* name, unsigned int diameter, bool life, unsigned int satelliteCount);
    planet(const planet& o);
    ~planet();

    char* getName() const;
    unsigned int getDiameter() const;
    bool getContainsLife() const;
    unsigned int getSatelliteCount() const;

    void setName(char* n);
    void setDiameter(unsigned int i);
    void setLife(bool b);
    void setSatelliteCount(unsigned int i);

    void print();

    planet& operator=(const planet& p);
    friend bool operator==(const planet& lhs, const planet& rhs);
    friend bool operator!=(const planet& lhs, const planet& rhs);
    friend bool operator<(const planet& lhs, const planet& rhs);

 private:
    char* name = nullptr;
    unsigned int diameter = 0;
    bool containsLife = false;
    unsigned int satelliteCount = 0;
};

std::istream& operator>>(std::istream& in, planet& p);

std::ifstream& operator>>(std::ifstream& in, planet& p);
std::ofstream& operator<<(std::ofstream& out, const planet& p);
}  // namespace planet
