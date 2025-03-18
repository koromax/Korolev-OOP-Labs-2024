#include "Animal.h"

#include <cstring>
#include <iomanip>
#include <iostream>

void Animal::increaseZoo() {
    zooCapacity = zooCapacity << 1;
    Animal** buffer = new Animal*[zooCapacity];

    std::copy(zoo, zoo + zooSize, buffer);

    Animal** oldSystem = zoo;
    zoo = buffer;

    delete[] oldSystem;
}

void Animal::SetName(const char* n) {
    if (name != nullptr) {
        delete[] name;
    }
    name = new char[std::strlen(n) + 1];
    std::strncpy(name, n, std::strlen(n) + 1);
}

Animal::Animal(const char* n, int a) : age(a) {
    SetName(n);
    std::cout << "Animal()" << std::endl;
}

Animal::Animal(const Animal& a) : age(a.age) {
    SetName(a.name);
    std::cout << "Animal()" << std::endl;
}

Animal& Animal::operator=(const Animal& o) {
    SetName(o.name);
    age = o.age;

    return *this;
}

void Animal::AddAnimal() {
    if (zooSize == zooCapacity) {
        increaseZoo();
    }
    zoo[zooSize] = this;
    zooSize++;
}

void Mammal::show() const {
    std::cout << std::right << std::setw(19) << "Mammal info: " << std::left << std::setw(20) << name << ", " << std::setw(3) << age << ", "
              << std::setw(6) << (hasFur ? "yesFur" : "noFur") << '\n';
}

void Bird::show() const {
    std::cout << std::right << std::setw(19) << "Bird info: " << std::left << std::setw(20) << name << ", " << std::setw(3) << age << ", "
              << std::setw(6) << wingSpan << '\n';
}

void Artiodactyl::show() const {
    std::cout << std::right << std::setw(19) << "Artiodactyl info: " << std::left << std::setw(20) << name << ", " << std::setw(3) << age << ", "
              << std::setw(6) << (hasFur ? "yesFur" : "noFur") << ", ";
    if (hoofCount != 0) {
        std::cout << hoofCount << '\n';
    } else {
        std::cout << "Cetacean" << '\n';
    }
}

int Animal::zooSize = 0;
int Animal::zooCapacity = 8;
Animal** Animal::zoo = new Animal*[Animal::zooCapacity];
