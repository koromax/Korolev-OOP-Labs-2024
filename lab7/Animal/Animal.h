#pragma once

#include <iostream>

// 14	млекопитающие, парнокопытные, птицы, животное

class Animal {
 protected:
    char* name;
    int age = 0;

    static Animal** zoo;
    static int zooSize;
    static int zooCapacity;

    void increaseZoo();

 public:
    Animal(const char* n, int a = 0) : age(a) {
        SetName(n);
        std::cout << "Animal()" << std::endl;
    };
    Animal(const Animal& a) : age(a.age) {
        SetName(a.name);
        std::cout << "Animal()" << std::endl;
    };
    virtual ~Animal() {
        delete[] name;
        std::cout << "~Animal()" << std::endl;
    }

    void SetName(const char* n);

    void AddAnimal();

    virtual void show() const = 0;
};

class Mammal : public Animal {
 protected:
    bool hasFur = false;

 public:
    Mammal(const char* n, int a = 0, bool fur = false) : Animal(n, a), hasFur(fur) { std::cout << "Mammal()" << std::endl; }
    Mammal(const Mammal& m) : Animal(m), hasFur(m.hasFur) { std::cout << "Mammal()" << std::endl; }
    ~Mammal() { std::cout << "~Mammal()" << std::endl; }

    void show() const override;
};

class Bird : public Animal {
 protected:
    double wingSpan = 0;

 public:
    Bird(const char* n, int a = 0, double w = 1.) : Animal(n, a), wingSpan(w) { std::cout << "Bird()" << std::endl; }
    Bird(const Bird& b) : Animal(b), wingSpan(b.wingSpan) { std::cout << "Bird()" << std::endl; }
    ~Bird() { std::cout << "~Bird()" << std::endl; }

    void show() const override;
};

class Artiodactyl : public Mammal {
 protected:
    int hoofCount = 4;

 public:
    Artiodactyl(const char* n, int a = 0, bool fur = false, int h = 4) : Mammal(n, a, fur), hoofCount(h) {
        std::cout << "Artiodactyl()" << std::endl;
    }
    Artiodactyl(const Artiodactyl& a) : Mammal(a), hoofCount(a.hoofCount) { std::cout << "Artiodactyl()" << std::endl; }
    ~Artiodactyl() { std::cout << "~Artiodactyl()" << std::endl; }

    void show() const override;
};
