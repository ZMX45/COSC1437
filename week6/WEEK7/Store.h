#ifndef STORE_H
#define STORE_H

#include "Product.h"
#include <iostream>

using namespace std;

class Store {
private:
    Product<int>* inventory;
    int numProducts;
    int capacity;

    // Resize inventory
    void resizeInventory(int newCapacity);

public:
    Store();  // Constructor
    ~Store(); // Destructor

    // Add product
    void addProduct(const Product<int>& p);

    // Display inventory
    void displayInventory() const;

    // Get product ID
    Product<int>& getProductByID(int productID);
};

#endif

