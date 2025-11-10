#include <iostream>
#include <limits>
#include "ParkingLot.h"

using namespace std;

// Function to safely get an integer choice
int getValidatedChoice() {
    int choice;
    while (true) {
        cout << "Enter your choice: ";
        if (cin >> choice) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer
            return choice;
        } else {
            cout << "Invalid input! Please enter a number between 1 and 4.\n";
            cin.clear(); // clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard wrong input
        }
    }
}

int main() {
    ParkingLot lot(3);
    int choice = 0;

    cout << "=====================================\n";
    cout << "   Car Parking Management System\n";
    cout << "=====================================\n";

    do {
        cout << "\n---------- MENU ----------\n";
        cout << "1. Park Car\n";
        cout << "2. Remove Car\n";
        cout << "3. Display Status\n";
        cout << "4. Exit\n";
        cout << "--------------------------\n";

        choice = getValidatedChoice(); // safe input

        switch (choice) {
            case 1: {
                Car c;
                cout << "\nEnter car number: ";
                getline(cin, c.number);
                cout << "Enter owner name: ";
                getline(cin, c.owner);
                lot.parkCar(c);
                break;
            }

            case 2: {
                if (!lot.is_empty()) {
                    string num;
                    cout << "\nEnter car number to remove: ";
                    getline(cin, num);
                    lot.removeCar(num);
                } else {
                    cout << "\nParking Lot is empty, no car to remove.\n";
                }
                break;
            }

            case 3:
                lot.displayStatus();
                break;

            case 4:
                cout << "\nExiting system... Thank you!\n";
                break;

            default:
                cout << "\nInvalid choice. Please select between 1 and 4.\n";
                break;
        }

    } while (choice != 4);

    return 0;
}
