// including ability to use other files
#ifndef zoo_h
#define zoo_h
#include "Animal.h"
#include "Mammal.h"
#include "Bird.h"
#include "Reptile.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Zoo{
private:
    Animal** animals;
    int numAnimals;
    int maxAnimals;

void resize() { // resize array method
        maxAnimals *= 2;
        Animal** newAnimals = new Animal*[maxAnimals];
        for (int i = 0; i < numAnimals; i++) {
            newAnimals[i] = animals[i];
        }
        delete[] animals;
        animals = newAnimals;
    }

public:
    Zoo() : numAnimals(0), maxAnimals(10) { // constructor
        animals = new Animal*[maxAnimals];
    }

    ~Zoo() { // destructor
        for (int i = 0; i < numAnimals; i++) {
            delete animals[i];
        }
        delete[] animals;
    }

    void addAnimal(Animal* animal) { // method to add animals
        if (numAnimals == maxAnimals) {
            resize();
        }
        animals[numAnimals++] = animal;
    }

    void removeAnimal(int index) { // method to remove animals from array
        if (index >= 0 && index < numAnimals) {
            delete animals[index];
            for (int i = index; i < numAnimals - 1; i++) {
                animals[i] = animals[i + 1];
            }
            numAnimals--;
        }
    }

    void displayAnimals() const { // print zoo method
        for (int i = 0; i < numAnimals; i++) {
            animals[i]->displayInfo();
        }
    }

    void saveToFile(const string& filename) const { // save list to text file
        ofstream outFile(filename);
        for (int i = 0; i < numAnimals; ++i) {
            outFile << animals[i]->name << " "
                    << animals[i]->age << " "
                    << animals[i]->species << endl;
        }
    }

    void loadFromFile(const string& filename) { // load file to program
        ifstream inFile(filename);
        string name, species;
        int age;
        while (inFile >> name >> age >> species){
            addAnimal(new Mammal(name, age, species));
        }
    }
};

#endif