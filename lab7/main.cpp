#include <iostream>

#include "Animal/Animal.h"

void print(Animal::zoo v) {
    for (int i = 0; i < Animal::zooSize; ++i) {
        (*v[i]).show();
    }
}

void clear(Animal::zoo v) {
    for (int i = Animal::zooSize - 1; i >= 0; --i) {
        v.delete_element(i);
    }
}

int main() {
    Animal* zoo;
    Mammal m("test", 0);
    zoo.add_element(&m);
    Bird b("UFO", 100, 25.5);
    zoo.add_element(&b);
    Artiodactyl a1("drunk drivers", 46, true, 2);
    Artiodactyl a2("killer whales", 240, false, 0);
    zoo.add_element(&a1);
    zoo.add_element(&a2);

    print(zoo);

    return 0;
}
