#include <iostream>
#include <exception>
#include <limits>

using namespace std;

// Custom exception class
class InvalidMileageException : public exception {
public:
    InvalidMileageException() {
        message = "You entered an invalid value, Try Again.";
    }

    InvalidMileageException(string str) {
        message = str;
    }

    const char* what() const noexcept override {
        return message.c_str();
    }

private:
    string message;
};

// Function to calculate the mileage, with exception handling
void calculateMileage(double strMil, double desMil) {
    cout << "In calculateMileage function" << endl;  // Stack unwinding demonstration
    
    if (strMil < 0 || desMil < 0 || desMil < strMil) {
        throw InvalidMileageException("Mileage values are invalid.");
    }
    
    double milTrvl = desMil - strMil;  // Calculate miles traveled
    cout << "You must travel " << milTrvl << " Miles to reach your destination." << endl;
}

int main() {
    // Variables to store starting miles and destination miles
    double strMil;
    double desMil;

    // Looping the prompt to enter value if invalid user input is given
    while (true) {
        try {
            // Prompting user to enter Starting Mileage and setting strMil to user input
            cout << "Enter Starting Mileage: " << endl;
            cin >> strMil;
            
            // Check for invalid input
            if (cin.fail() || strMil < 0) {
                cin.clear();  // Clear the error
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore the invalid input
                throw InvalidMileageException();
            }

            cout << "You Entered: " << strMil << " Miles." << endl;
            cout << "\n";

            // Prompting user to enter Destination Mileage and setting desMil to user input
            cout << "Enter Destination Mileage: " << endl;
            cin >> desMil;
            
            // Check for invalid input
            if (cin.fail() || desMil < 0 || desMil < strMil) {
                cin.clear();  // Clear the error
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore the invalid input
                throw InvalidMileageException();
            }

            cout << "You Entered: " << desMil << " Miles." << endl;
            cout << "\n";

            // Calling function to calculate mileage
            cout << "Before calling calculateMileage function" << endl; // Stack unwinding
            calculateMileage(strMil, desMil);

            // If everything is valid, break out of the loop
            break;

        } catch (InvalidMileageException& IMEV) {
            cout << IMEV.what() << endl;
        }
    }

    return 0;
}
