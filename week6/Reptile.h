//defining reptile class
#ifndef Reptile_h
#define Reptile_h

#include "Animal.h" // including the abstract animal class to derive from

using namespace std;

class Reptile : public Animal{    //deriving from animal class
public:
    Reptile(string n, int a, string s){ // constructor
        name = n;
        age = a;
        species = s;
    }

    virtual void makeSound() const{ // animal sound method
        cout << name << "\"Hiss\"";
    }
    virtual void displayInfo() const{ // print animal method
        cout << "Reptile's name" << name << " Reptile's age: " << age << " Species of reptile: " << endl;
    }

    Reptile(); // default constructor
};
#endif