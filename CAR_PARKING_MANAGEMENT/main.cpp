#include <iostream>
#include <limits>
#include "ParkingLot.h"
using namespace std;

int main() {
    ParkingLot lot(3);
    int choice;

    do {
        cout << "\n1. Park Car\n2. Remove Car\n3. Display Status\n4. Exit\nChoice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            Car c;
            cout << "Enter car number: ";
            getline(cin, c.number);
            cout << "Enter owner name: ";
            getline(cin, c.owner);
            lot.parkCar(c);
        } 
        else if (choice == 2) {
            string num;
            cout << "Enter car number to remove: ";
            getline(cin, num);
            lot.removeCar(num);
        } 
        else if (choice == 3) {
            lot.displayStatus();
        } 
        else if (choice != 4) {
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);

    cout << "Exiting system.\n";
    return 0;
}
