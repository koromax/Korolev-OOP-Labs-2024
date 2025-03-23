#include <iostream>

#include "Animal/Animal.h"

void print(Animal** zoo = Animal::zoo, const int zooSize = Animal::zooSize) {
    if (zooSize == 0) {
        std::cout << "All animals have run away..." << '\n';
        return;
    }

    for (int i = 0; i < zooSize; ++i) {
        std::cout << i + 1 << ". ";
        (*zoo[i]).show();
    }
}

void deleteElem(int i = 0, Animal** zoo = Animal::zoo, int& zooSize = Animal::zooSize) {
    if (i < 0 || i > zooSize) {
        std::cerr << "The index is out of bounds." << '\n';
        return;
    }

    int j = 0;
    while (j < Animal::zooSize && Animal::zoo[j] != zoo[i]) {
        j++;
    }

    while (j < Animal::zooSize - 1) {
        Animal::zoo[j] = Animal::zoo[j + 1];
        ++j;
    }
    Animal::zooSize--;

    if (zoo != Animal::zoo) {
        while (i < zooSize - 1) {
            zoo[i] = zoo[i + 1];
            ++i;
        }
        zooSize--;
    }
}

void clear(Animal** zoo = Animal::zoo, int& zooSize = Animal::zooSize) {
    while (zooSize > 0) {
        deleteElem(0, zoo, zooSize);
    }
}

int main() {
    Mammal m("sphinx", 4500);
    Bird b("government spy drones", 17, 25.5);
    Artiodactyl a1("drunk drivers", 06, true, 2);
    Artiodactyl a2("killer whales", 14, false, 0);

    int myPetsAmount = 3;
    Animal* myPets[myPetsAmount];
    myPets[0] = new Mammal("Dog 🐕", 5);
    myPets[1] = new Bird("Parrot 🦜", 1, .46);
    myPets[2] = new Artiodactyl("Sheep 🐑", 7, true, 4);
    int masLength = 3;

    print();
    std::cout << '\n';

    deleteElem(2, myPets, myPetsAmount);
    print();
    std::cout << '\n';

    deleteElem(2, myPets, myPetsAmount);
    print(myPets, myPetsAmount);
    std::cout << '\n';

    deleteElem(1);
    print();
    std::cout << '\n';

    for (int i = 0; i < myPetsAmount; ++i) {
        delete myPets[i];
    }
    delete[] Animal::zoo;
    return 0;
}
