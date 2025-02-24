// defining mammal class
#ifndef Mammal_h
#define Mammal_h

#include "Animal.h" // including the abstract animal class to derive from

using namespace std;

class Mammal : public Animal{    //deriving from animal class
public:
    Mammal(string n, int a, string s){ // constructor
        name = n;
        age = a;
        species = s;
    }

    virtual void makeSound() const{ // animal sound method
        cout << name << " \"Hello I'm " << name << "\"" << endl;
    }
    virtual void displayInfo() const{ // print method
        cout << "Mammal's name: " << name << " Mammal's age: " << age << " Species of mammal: " << species << endl;
    }

    Mammal(); // default constructor
};
#endif