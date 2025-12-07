#include <iostream>
#include <limits>
#include <iomanip>
#include <ctime>
#include "ParkingLot.h"
#include <cstring>
#include <chrono>
using namespace std;

using hr = chrono::high_resolution_clock;

auto time_op = [](auto func)
{
    auto t1 = hr::now();
    func();
    auto t2 = hr::now();
    return chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
};

// Clear input buffer safely
void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Format time to readable string
string formatTime(time_t t)
{
    char buffer[26];
    strncpy(buffer, ctime(&t), sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    return string(buffer);
}

// Validate menu choice
int getMenuChoice()
{
    int choice;
    while (true)
    {
        cout << "\nEnter your choice (1-4): ";
        if (cin >> choice && choice >= 1 && choice <= 4)
        {
            clearInput();
            return choice;
        }
        cout << " Invalid choice! Please enter a number between 1 and 4.\n";
        clearInput();
    }
}

// Display main menu
void showMenu()
{
    cout << "\n=====================================\n";
    cout << "          Parking System Menu\n";
    cout << "=====================================\n";
    cout << "  1. Park Car\n";
    cout << "  2. Remove Car\n";
    cout << "  3. Display Status\n";
    cout << "  4. Exit\n";
    cout << "-------------------------------------\n";
}

int main()
{
    ParkingLot lot(3);
    int choice = 0;

    cout << "===========================================\n";
    cout << "      Car Parking Management System\n";
    cout << "===========================================\n";

    do
    {
        showMenu();
        choice = getMenuChoice();

        switch (choice)
        {

        // ------------ PARK CAR ------------
        case 1:
        {
            Car c;
            cout << "\n Enter Car Number: ";
            getline(cin, c.number);
            while (c.number.empty())
            {
                cout << " Car number cannot be empty. Enter again: ";
                getline(cin, c.number);
            }

            cout << " Enter Owner Name: ";
            getline(cin, c.owner);
            while (c.owner.empty())
            {
                cout << " Owner name cannot be empty. Enter again: ";
                getline(cin, c.owner);
            }

            // Set entry time
            c.entryTime = time(0);

            // Park the car
            auto duration = time_op([&]()
                                    { lot.parkCar(c); });

            cout << "\nTime Taken: " << duration << " microseconds\n";

            // Show entry time nicely
            cout << left << setw(15) << "Entry Time:"
                 << formatTime(c.entryTime) << "\n";

            break;
        }

        // ------------ REMOVE CAR ------------
        case 2:
        {
            if (lot.is_empty())
            {
                cout << "\n Parking lot is empty. Nothing to remove.\n";
                break;
            }

            string num;
            cout << "\n  Enter Car Number to Remove: ";
            getline(cin, num);
            while (num.empty())
            {
                cout << " Car number cannot be empty. Enter again: ";
                getline(cin, num);
            }
            double fee;
            // Remove car and display fee formatted
            auto duration = time_op([&]()
                                    { fee = lot.removeCar(num); });

            cout << "Remove Time: " << duration << " microseconds\n";

            if (fee >= 0)
            {
                cout << fixed << setprecision(2); // 2 decimal places
                cout << " Parking Fee: Rs. " << fee << "\n";
            }
            else
            {
                cout << "Car not found, please check the number.\n";
            }

            break;
        }
        // ------------ STATUS ------------
        case 3:
        {
            cout << "\n CURRENT PARKING STATUS:\n";
            cout << left << setw(10) << "Car #"
                 << setw(15) << "Owner"
                 << setw(25) << "Entry Time" << "\n";
            cout << "-----------------------------------------------\n";
            lot.displayStatus();
            break;
        }

        // ------------ EXIT ------------
        case 4:
            cout << "\n Exiting System... Thank you for using our service!\n";
            break;
        }

    } while (choice != 4);

    return 0;
}
