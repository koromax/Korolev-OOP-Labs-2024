#include <iostream>

#include "Animal/Animal.h"

void print(Animal** zoo) {
    for (int i = 0; i < Animal::zooSize; ++i) {
        (*zoo[i]).show();
    }
}

void deleteElem(Animal** zoo, int i = 0) {
    delete (zoo[i]);
    while (i < Animal::zooSize) {
        zoo[i] = zoo[i + 1];
        ++i;
    }
    Animal::zooSize--;
}

void clear(Animal** zoo) {
    while (Animal::zooSize > 0) {
        deleteElem(zoo);
    }
}

int main() {
    Mammal m("test", 0);
    m.AddAnimal();
    Bird b("UFO", 100, 25.5);
    b.AddAnimal();
    Artiodactyl a1("drunk drivers", 46, true, 2);
    Artiodactyl a2("killer whales", 240, false, 0);
    a1.AddAnimal();
    a2.AddAnimal();

    print(Animal::zoo);

    return 0;
}
