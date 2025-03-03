// defining bird class
#ifndef Bird_h
#define Bird_h

#include "Animal.h" // including the abstract animal class to derive from

using namespace std;

class Bird : public Animal{     //deriving from animal class
public:
    Bird(string n, int a, string s){ // constructor
        name = n;
        age = a;
        species = s;
    }

    virtual void makeSound() const{ // sound method
        cout << name << "\"Chirp\"";
    }
    virtual void displayInfo() const{ // print method
        cout << "Bird's name: " << name << " Bird's age: " << age << " Species of bird: " << species << endl;
    }

    Bird(); // default constructor

};
#endif