#pragma once

#include <fstream>
#include <iostream>

namespace planet {
class planet {
 public:
    planet();
    planet(char* name, unsigned int diameter, bool life, unsigned int satelliteCount);
    ~planet();

    char* getName();
    unsigned int getDiameter();
    bool getContainsLife();
    unsigned int getSatelliteCount();

    void setName(char* n);
    void setDiameter(unsigned int i);
    void setLife(bool b);
    void setSatelliteCount(unsigned int i);

    void print();

    friend bool operator==(const planet& lhs, const planet& rhs);
    friend bool operator!=(const planet& lhs, const planet& rhs);
    friend bool operator<(const planet& lhs, const planet& rhs);
    planet& operator=(const planet& p);

 private:
    char* name = nullptr;
    unsigned int diameter = 0;
    bool containsLife = false;
    unsigned int satelliteCount = 0;
};

std::istream& operator>>(std::istream& in, planet& p);

std::ifstream& operator>>(std::ifstream& in, planet& p);
std::ofstream& operator<<(std::ofstream& out, planet& p);
}  // namespace planet
