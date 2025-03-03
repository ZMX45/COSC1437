#include "Product.h"
#include "Store.h"
 
int main() {
    Product<int> laptop("Laptop", 999.99, Product<double>::generateStock(10, 50));
    Product<int> phone("Phone", 599.99, 20);
    Store myStore;
 
    cout << "Initial Inventory:\n";
    cout << laptop << phone;
 
    // Sell a product
    laptop = laptop - 5;
 
    cout << "After Selling 5 Laptops:\n";
    cout << laptop;
 
    // Apply discount
    applyDiscount(laptop, 10);
    cout << "After 10% Discount on Laptop:\n";
    cout << laptop;
 
    myStore.addProduct(laptop);
    cout << "myStore's Inventory: " << endl;
    myStore.displayInventory();
    
    myStore.addProduct(phone);
    cout << "myStore after adding phones to inventory: " << endl;
    myStore.displayInventory();

    return 0;
}