#include "Store.h"

// Constructor
Store::Store() : numProducts(0), capacity(2) {
    inventory = new Product<int>[capacity];
}

// Destructor
Store::~Store() {
    delete[] inventory;
}

// Resize inventory
void Store::resizeInventory(int newCapacity) {
    Product<int>* newInventory = new Product<int>[newCapacity];

    for (int i = 0; i < numProducts; i++) {
        newInventory[i] = inventory[i];
    }

    delete[] inventory;  // Deallocate
    inventory = newInventory;
    capacity = newCapacity;
}

// Add product
void Store::addProduct(const Product<int>& p) {

    if (numProducts >= capacity) {
        cout << "Inventory is full!" << endl;
    }

    inventory[numProducts++] = p;
}

// Display store inventory
void Store::displayInventory() const {
    for (int i = 0; i < numProducts; i++) {
        cout << inventory[i];
    }
}

// Get product ID
Product<int>& Store::getProductByID(int productID) {
    for (int i = 0; i < numProducts; i++) {
        if (inventory[i].getProductID() == productID) {
            return inventory[i];
        }
    }

    static Product<int> notFoundProduct;
    return notFoundProduct;
}
