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
    if (j == Animal::zooSize) {
        std::cerr << "somehow the animal has escaped the static zoo..." << '\n';
        return;
    }

    (Animal::zoo[j])->~Animal();
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
    Mammal* m = new Mammal("test", 0);
    Bird* b = new Bird("UFO", 100, 25.5);
    Artiodactyl* a1 = new Artiodactyl("drunk drivers", 46, true, 2);
    Artiodactyl* a2 = new Artiodactyl("killer whales", 240, false, 0);

    Animal* mas[3];
    mas[0] = new Mammal("654", 9);
    mas[1] = new Bird("jr", 20, 1.5);
    mas[2] = new Artiodactyl("!!!", 942, true);
    int masLength = 3;

    print(mas, masLength);
    std::cout << '\n';
    deleteElem(2, mas, masLength);
    print(mas, masLength);
    std::cout << '\n';

    clear(mas, masLength);

    print();
    std::cout << '\n';
    deleteElem(1);
    print();
    std::cout << '\n';
    clear();
    print();
    return 0;
}
