// defining animal class
#ifndef Animal_h
#define Animal_h

#include <iostream>

using namespace std;

//animal is an abstract class and cannot create an object
class Animal{
public:
// traits of animal class
    string name;
    string species;
    int age;

// virtual functions do not have definitions
    virtual void makeSound() const = 0;
    virtual void displayInfo() const = 0;

};
#endif