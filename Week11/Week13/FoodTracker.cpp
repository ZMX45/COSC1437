
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

using namespace std;

template<typename T>
void inputValidated(T& var, const string& prompt) {
    while (true) {
        cout << prompt;
        cin >> var;
        if (cin.fail() || var < 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Try again.\n";
        } else break;
    }
}

struct FoodNode {
    string foodName;
    float protein;
    float carbs;
    float fat;
    FoodNode* next;

    FoodNode(string name, float p, float c, float f)
        : foodName(name), protein(p), carbs(c), fat(f), next(nullptr) {}
};

class FoodTracker {
private:
    FoodNode* head;

    float calculateCalories(float protein, float carbs, float fat) const {
        return (protein * 4) + (carbs * 4) + (fat * 9);
    }

    void printBar(const string& label, float value, float total) const {
        int length = static_cast<int>((value / total) * 30);
        cout << label << ": [";
        for (int i = 0; i < length; ++i) cout << "#";
        for (int i = length; i < 30; ++i) cout << " ";
        cout << "] " << fixed << setprecision(1) << (value / total * 100) << "%\n";
    }

public:
    FoodTracker() : head(nullptr) {}

    ~FoodTracker() {
        saveToFile("autosave.txt");
        while (head) {
            FoodNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addFood(const string& name, float p, float c, float f) {
        FoodNode* newNode = new FoodNode(name, p, c, f);
        if (!head) head = newNode;
        else {
            FoodNode* current = head;
            while (current->next) current = current->next;
            current->next = newNode;
        }
        cout << "Food added.\n";
    }

    bool removeFood(const string& name) {
        FoodNode* current = head;
        FoodNode* prev = nullptr;

        while (current) {
            if (current->foodName == name) {
                if (!prev) head = current->next;
                else prev->next = current->next;
                delete current;
                cout << "Food removed.\n";
                return true;
            }
            prev = current;
            current = current->next;
        }
        cout << "Food not found.\n";
        return false;
    }

    bool editFood(const string& name) {
        FoodNode* current = head;
        while (current) {
            if (current->foodName == name) {
                cout << "Editing " << name << ":\n";
                inputValidated(current->protein, "New protein (g): ");
                inputValidated(current->carbs, "New carbs (g): ");
                inputValidated(current->fat, "New fat (g): ");
                cout << "Food updated.\n";
                return true;
            }
            current = current->next;
        }
        cout << "Food not found.\n";
        return false;
    }

    void displayFoods() const {
        if (!head) {
            cout << "No foods recorded.\n";
            return;
        }
        FoodNode* current = head;
        cout << fixed << setprecision(2);
        while (current) {
            cout << current->foodName << ": Protein=" << current->protein
                 << "g, Carbs=" << current->carbs << "g, Fat=" << current->fat
                 << "g, Calories=" << calculateCalories(current->protein, current->carbs, current->fat) << '\n';
            current = current->next;
        }
    }

    void displayTotals(bool showChart = false) const {
        float totalProtein = 0, totalCarbs = 0, totalFat = 0;
        FoodNode* current = head;
        while (current) {
            totalProtein += current->protein;
            totalCarbs += current->carbs;
            totalFat += current->fat;
            current = current->next;
        }
        float totalCalories = calculateCalories(totalProtein, totalCarbs, totalFat);
        cout << fixed << setprecision(2)
             << "\nTotal Protein: " << totalProtein << "g\n"
             << "Total Carbs: " << totalCarbs << "g\n"
             << "Total Fat: " << totalFat << "g\n"
             << "Total Calories: " << totalCalories << " kcal\n";

        if (showChart) {
            float sum = totalProtein + totalCarbs + totalFat;
            if (sum > 0) {
                cout << "\nMacro Pie Chart:\n";
                printBar("Protein", totalProtein, sum);
                printBar("Carbs  ", totalCarbs, sum);
                printBar("Fat    ", totalFat, sum);
            }
        }
    }

    void searchFood(const string& name) const {
        FoodNode* current = head;
        while (current) {
            if (current->foodName == name) {
                cout << fixed << setprecision(2)
                     << current->foodName << ": Protein=" << current->protein
                     << "g, Carbs=" << current->carbs << "g, Fat=" << current->fat
                     << "g, Calories=" << calculateCalories(current->protein, current->carbs, current->fat) << '\n';
                return;
            }
            current = current->next;
        }
        cout << "Food not found.\n";
    }

    void sortFoods() {
        if (!head || !head->next) return;
        bool swapped;
        do {
            swapped = false;
            FoodNode* current = head;
            FoodNode* prev = nullptr;
            while (current->next) {
                if (current->foodName > current->next->foodName) {
                    FoodNode* temp = current->next;
                    current->next = temp->next;
                    temp->next = current;
                    if (!prev) head = temp;
                    else prev->next = temp;
                    prev = temp;
                    swapped = true;
                } else {
                    prev = current;
                    current = current->next;
                }
            }
        } while (swapped);
        cout << "Foods sorted alphabetically.\n";
    }

    void saveToFile(const string& filename) const {
        ofstream outFile(filename);
        if (!outFile) {
            cout << "Error writing to file.\n";
            return;
        }
        FoodNode* current = head;
        while (current) {
            outFile << current->foodName << " "
                    << current->protein << " "
                    << current->carbs << " "
                    << current->fat << '\n';
            current = current->next;
        }
        outFile.close();
        cout << "Data saved to " << filename << '\n';
    }

    void loadFromFile(const string& filename) {
        ifstream inFile(filename);
        if (!inFile) {
            cout << "Error reading from file.\n";
            return;
        }
        string name;
        float p, c, f;
        while (inFile >> name >> p >> c >> f) {
            addFood(name, p, c, f);
        }
        inFile.close();
        cout << "Data loaded from " << filename << '\n';
    }
};

void showMenu() {
    FoodTracker tracker;
    int choice;
    string name, filename;
    float p, c, f;

    do {
        cout << "\nFood Tracker Menu:\n"
             << "1. Add Food\n"
             << "2. Remove Food\n"
             << "3. Edit Food\n"
             << "4. Display All Foods\n"
             << "5. Display Macro Totals + Chart\n"
             << "6. Search for a Food\n"
             << "7. Sort Foods Alphabetically\n"
             << "8. Save to File\n"
             << "9. Load from File\n"
             << "10. Exit\n"
             << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter food name: ";
                getline(cin, name);
                inputValidated(p, "Protein (g): ");
                inputValidated(c, "Carbs (g): ");
                inputValidated(f, "Fat (g): ");
                tracker.addFood(name, p, c, f);
                break;
            case 2:
                cout << "Enter food name to remove: ";
                getline(cin, name);
                tracker.removeFood(name);
                break;
            case 3:
                cout << "Enter food name to edit: ";
                getline(cin, name);
                tracker.editFood(name);
                break;
            case 4:
                tracker.displayFoods();
                break;
            case 5:
                tracker.displayTotals(true);
                break;
            case 6:
                cout << "Enter food name to search: ";
                getline(cin, name);
                tracker.searchFood(name);
                break;
            case 7:
                tracker.sortFoods();
                break;
            case 8:
                cout << "Enter filename to save: ";
                getline(cin, filename);
                tracker.saveToFile(filename);
                break;
            case 9:
                cout << "Enter filename to load: ";
                getline(cin, filename);
                tracker.loadFromFile(filename);
                break;
            case 10:
                cout << "Exiting and saving...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }

        if (choice != 10) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            system(CLEAR);
        }

    } while (choice != 10);
}

int main() {
    showMenu();
    return 0;
}
