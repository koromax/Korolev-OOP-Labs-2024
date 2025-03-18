#include "Animal.h"

#include <cstring>
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
    name = new char[std::strlen(n) + 1];
    std::strncpy(name, n, std::strlen(n) + 1);
}

void Animal::AddAnimal() {
    if (zooSize == zooCapacity) {
        increaseZoo();
    }
    zoo[zooSize] = this;
    zooSize++;
}

void Mammal::show() const {
    std::cout << "Mammal info: " << name << ", " << age << ", " << (hasFur ? "yesFur" : "noFur") << '\n';
}

void Bird::show() const {
    std::cout << "Bird info: " << name << ", " << age << ", " << wingSpan << '\n';
}

void Artiodactyl::show() const {
    std::cout << "Artiodactyl info: " << name << ", " << age << ", " << (hasFur ? "yesFur" : "noFur") << ", ";
    if (hoofCount != 0) {
        std::cout << hoofCount << '\n';
    } else {
        std::cout << "Cetacean" << '\n';
    }
}

int Animal::zooSize = 0;
int Animal::zooCapacity = 8;
Animal** Animal::zoo = new Animal*[Animal::zooCapacity];
