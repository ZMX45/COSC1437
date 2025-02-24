//adding the ability to use code from header files
#include <iostream>
#include "Animal.h"
#include "Mammal.h"
#include "Bird.h"
#include "Reptile.h"
#include "Zoo.h"

using namespace std;

void displayMenu(){ // creating ui menu
    cout << "1. Add an animal" << endl;
    cout << "2. Remove an animal" << endl;
    cout << "3. Display all animals" << endl;
    cout << "4. Save animals to file" << endl;
    cout << "5. Load animals from file" << endl;
    cout << "6. Exit" << endl;
}

int main(){
    Zoo myZoo; // creating a zoo object

    myZoo.loadFromFile("zoo_data.txt"); // loading file for data

    int choice; // coding each choice in ui
    do {
        displayMenu(); // open ui menu
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: { // creating new animal
            string name, species;
            int age;
            cout << "Enter animal name: ";
            getline(cin, name);
            cout << "Enter animal age: ";
            cin >> age;
            cin.ignore();
            cout << "Enter animal species: ";
            getline(cin, species);
            myZoo.addAnimal(new Mammal(name, age, species));
            break;
        }
        case 2: { // removing animal from array
            int index;
            cout << "Enter animal index to remove: ";
            cin >> index;
            myZoo.removeAnimal(index);
            break;
        }
        case 3: // print zoo array 
            myZoo.displayAnimals();
            break;
        case 4: // save array to file
            myZoo.saveToFile("zoo_data.txt");
            break;
        case 5: // load array from file
            myZoo.loadFromFile("zoo_data.txt");
            break;
        case 6: // exit program
            cout << "Exiting...\n";
            break;
        default: // choice to make sure user inputs proper answer
            cout << "Invalid choice!\n";
        }
    } while (choice != 6); // repeating until user chooses exit


    return 0;
}

