#include <iostream>

#include "Animal/Animal.h"

void print(Animal** zoo) {
    if (Animal::zooSize == 0) {
        std::cout << "All animals have run away..." << '\n';
        return;
    }

    for (int i = 0; i < Animal::zooSize; ++i) {
        (*zoo[i]).show();
    }
}

void deleteElem(Animal** zoo, int i = 0) {
    (zoo[i])->~Animal();
    while (i < Animal::zooSize - 1) {
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
    Mammal* m = new Mammal("test", 0);
    (*m).AddAnimal();
    Bird* b = new Bird("UFO", 100, 25.5);
    (*b).AddAnimal();
    Artiodactyl* a1 = new Artiodactyl("drunk drivers", 46, true, 2);
    Artiodactyl* a2 = new Artiodactyl("killer whales", 240, false, 0);
    (*a1).AddAnimal();
    (*a2).AddAnimal();

    print(Animal::zoo);
    clear(Animal::zoo);
    print(Animal::zoo);
    return 0;
}
