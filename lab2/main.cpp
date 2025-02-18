#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "planet/planet.h"
#include "shop/shop.h"

namespace {
const int kBufferSize = 128;

template<typename T>
struct array {
    unsigned int size = 0;
    unsigned int capacity = 8;
    T* array = new T[capacity];
};

template<typename T>
void increaseArray(array<T>& s) {
    s.capacity = s.capacity << 1;
    T* buffer = new T[s.capacity];

    std::copy(s.array, s.array + s.size, buffer);

    T* oldSystem = s.array;
    s.array = buffer;

    delete[] oldSystem;
}

void PrintPlanetMenu() {
    std::cout << "Select action" << '\n';
    std::cout << "1) Add planet" << '\n';
    std::cout << "2) Remove planet" << '\n';
    std::cout << "3) Edit planet" << '\n';
    std::cout << "4) Print planets" << '\n';
    std::cout << "5) Load from file" << '\n';
    std::cout << "6) Write into file" << '\n';
    std::cout << "0) Exit" << '\n';
}

void PrintShopMenu() {
    std::cout << "Select action" << '\n';
    std::cout << "1) Add shop" << '\n';
    std::cout << "2) Remove shop" << '\n';
    std::cout << "3) Edit shop" << '\n';
    std::cout << "4) Print shops" << '\n';
    std::cout << "5) Load from file" << '\n';
    std::cout << "6) Write into file" << '\n';
    std::cout << "0) Exit" << '\n';
}

int ReadSelectionFromStdin() {
    int selection = 0;
    std::cin >> selection;
    return selection;
}

planet::planet ReadPlanetFromStdin() {
    std::cout << "Enter planet name, diameter, if it contains lifeforms [0/1] and amount of satellites : ";
    planet::planet p;
    std::cin >> p;
    return p;
}

shop::shop ReadShopFromStdin() {
    std::cout << "Enter shop name, type, area and if it's local[1 - True] : ";
    shop::shop s;
    std::cin >> s;
    return s;
}

template<typename T>
void Add(array<T>& s, T e) {
    if (s.size == s.capacity) {
        increaseArray(s);
    }

    int i = 0;
    while (i < s.size && s.array[i] < e) {
        ++i;
    }
    for (int j = s.size; j > i; --j) {
        s.array[j] = s.array[j - 1];
    }
    s.array[i] = e;
    ++s.size;
}

template<typename T>
void Remove(array<T>& s, T e) {
    int i = 0;
    while (i < s.size && s.array[i] != e) {
        ++i;
    }

    if (i == s.size) {
        std::cout << "Failed to find the item" << '\n';
        return;
    }

    ++i;
    while (i < s.size) {
        s.array[i - 1] = s.array[i];
        ++i;
    }

    --s.size;
}

void Edit(array<planet::planet>& s) {
    std::cout << "Select item to edit" << '\n';
    for (int i = 0; i < s.size; ++i) {
        std::cout << i + 1 << ") ";
        s.array[i].print();
    }
    std::cout << '\n';

    int selectedItem = 0;
    std::cin >> selectedItem;
    selectedItem--;

    int action = -1;
    while (action != 0) {
        s.array[selectedItem].print();
        std::cout << "Select field to edit: 1) Name 2) Diameter 3) Has life 4) Satellite amount  0) Exit" << '\n';
        std::cin >> action;

        switch (action) {
            case 1:
                char buffer[kBufferSize];
                std::cout << "Enter new name: ";
                std::cin >> buffer;
                s.array[selectedItem].setName(buffer);
                break;
            case 2:
                unsigned int diameter;
                std::cout << "Enter new diameter: ";
                std::cin >> diameter;
                s.array[selectedItem].setDiameter(diameter);
                break;
            case 3:
                bool life;
                std::cout << "Enter if planet contains lifeforms [0/1]: ";
                std::cin >> life;
                s.array[selectedItem].setLife(life == 1);
                break;
            case 4:
                unsigned int satelliteCount;
                std::cout << "Enter new satellite amount: ";
                std::cin >> satelliteCount;
                s.array[selectedItem].setSatelliteCount(satelliteCount);
                break;
            default:
                break;
        }
    }
}

void Edit(array<shop::shop>& s) {
    std::cout << "Select item to edit" << '\n';
    for (int i = 0; i < s.size; ++i) {
        std::cout << i + 1 << ") ";
        s.array[i].print();
    }
    std::cout << '\n';

    int selectedItem = 0;
    std::cin >> selectedItem;
    selectedItem--;

    int action = -1;
    while (action != 0) {
        s.array[selectedItem].print();
        std::cout << "Select field to edit: 1) Name 2) Type 3) Area 4) Is Local?  0) Exit" << '\n';
        std::cin >> action;

        switch (action) {
            case 1:
                char name[kBufferSize];
                std::cout << "Enter new name: ";
                std::cin >> name;
                s.array[selectedItem].setName(name);
                break;
            case 2:
                char type[kBufferSize];
                std::cout << "Enter shop type: ";
                std::cin >> type;
                s.array[selectedItem].setType(type);
                break;
            case 3:
                bool area;
                std::cout << "Enter shop's area: ";
                std::cin >> area;
                s.array[selectedItem].setArea(area);
                break;
            case 4:
                bool isLocal;
                std::cout << "Enter if shop is local [1 = True]: ";
                std::cin >> isLocal;
                s.array[selectedItem].setLocal(isLocal == 1);
                break;
            default:
                break;
        }
    }
}

template<typename T>
void LoadFromFile(array<T>& s, const char* fileName) {
    std::ifstream fileIn(fileName, std::ios::binary | std::ios::in);
    if (!fileIn.is_open()) {
        std::cout << "Failed to open file " << fileName << "\n";
        return;
    }

    char buffer[kBufferSize];
    if (fileIn.getline(buffer, sizeof(buffer))) {
        int length = std::atoi(buffer);

        T e;
        for (int i = 0; i < length; ++i) {
            fileIn >> e;
            Add(s, e);
        }
    }

    fileIn.close();
    std::cout << "Succesfully loaded from file." << '\n';
}

template<typename T>
void WriteIntoFile(array<T>& s, const char* fileName) {
    std::ofstream fileOut(fileName, std::ios::binary | std::ios::out | std::ios::trunc);
    if (!fileOut.is_open()) {
        std::cout << "Failed to open file " << fileName << "\n";
        return;
    }

    fileOut << s.size << '\n';
    for (int i = 0; i < s.size; ++i) {
        fileOut << s.array[i];
    }
    fileOut.close();
    std::cout << "Succesfully wrote into file." << '\n';
}
}  // namespace

void RunPlanet() {
    array<planet::planet> planets;
    LoadFromFile(planets, "lab2/SolarSystem.txt");

    while (true) {
        PrintPlanetMenu();
        switch (ReadSelectionFromStdin()) {
            case 1:
                Add(planets, ReadPlanetFromStdin());
                break;
            case 2:
                Remove(planets, ReadPlanetFromStdin());
                break;
            case 3:
                Edit(planets);
                break;
            case 4:
                for (int i = 0; i < planets.size; ++i) {
                    planets.array[i].print();
                }
                break;
            case 5:
                LoadFromFile(planets, "lab2/SolarSystem.txt");
                break;
            case 6:
                WriteIntoFile(planets, "lab2/SolarSystem.txt");
                break;
            default:
                return;
        }
    }
}

void RunVariant() {
    array<shop::shop> shops;
    LoadFromFile(shops, "lab2/Shops.txt");

    while (true) {
        PrintShopMenu();
        switch (ReadSelectionFromStdin()) {
            case 1:
                Add(shops, ReadShopFromStdin());
                break;
            case 2:
                Remove(shops, ReadShopFromStdin());
                break;
            case 3:
                Edit(shops);
                break;
            case 4:
                for (int i = 0; i < shops.size; ++i) {
                    shops.array[i].print();
                }
                break;
            case 5:
                LoadFromFile(shops, "lab2/Shops.txt");
                break;
            case 6:
                WriteIntoFile(shops, "lab2/Shops.txt");
                break;
            default:
                return;
        }
    }
}

int main(int argc, char** argv) {
    if (argc == 2 && std::strcmp(argv[1], "v") == 0) {
        RunVariant();
    } else {
        RunPlanet();
    }

    return 0;
}
