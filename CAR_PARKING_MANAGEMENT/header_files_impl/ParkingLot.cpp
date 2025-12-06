#include "ParkingLot.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <cstring>
#include <vector>

using namespace std;

ParkingLot::ParkingLot(int c) : lane(c), tempStack(c), waitingQueue(c), capacity(c) {}

void ParkingLot::parkCar(Car car) {
     car.entryTime = time(0);
    if (lane.getSizeOfLot() < capacity) {
        lane.push(car);
        cout << "Car \"" << car.number << "\" parked successfully.\n";
        saveToFileOnEntry(car, car.entryTime);

    } else {
        if(waitingQueue.size()<waitingQueue.Maxsize()){
            cout << "Parking full. Added to waiting queue.\n";
            waitingQueue.enqueue(car);
        }
        else{
            cout<<"Waiting queue is also full, please try later!!! THANKS.\n";
        }
    }
}
double ParkingLot::calculateFee(time_t entry, time_t exit) {
    double hours = difftime(exit, entry) / 3600.0;
    if (hours < 1) hours = 1;     // Minimum 1 hour charge

    double rate = 50;            // Rs. 50 per hour
    return hours * rate;
}

double ParkingLot::removeCar(string number) {
    bool found = false;
    Car removedCar;

    while (!lane.isEmpty()) {
        Car topCar = lane.peek();
        lane.pop();

        if (topCar.number == number) {
            found = true;
            removedCar = topCar;
            break;
        } else {
            tempStack.push(topCar);
        }
    }

    // Restore remaining cars
    while (!tempStack.isEmpty()) {
        lane.push(tempStack.peek());
        tempStack.pop();
    }

    if (!found) {
        cout << "Car not found.\n";
        return -1;   // indicate car not found
    }

    // Calculate fee
    time_t exitTime = time(0);
    double fee = calculateFee(removedCar.entryTime, exitTime);

    // Inform user and save to file
    cout << "Car removed. Fee: Rs. " << fixed << setprecision(2) << fee << "\n";
    saveToFileOnExit(removedCar, exitTime, fee);
    // Move next car from waiting queue if any
    if (!waitingQueue.isEmpty()) {
        Car next = waitingQueue.front();
        waitingQueue.dequeue();
        parkCar(next);
    }

    return fee;  // return the fee to main
}

void ParkingLot::displayStatus() {
    cout << "\n--- Parking Status ---\n";
    cout << "Total Capacity: " << capacity << endl;
    cout << "Occupied: " << lane.getSizeOfLot() << endl;
    cout << "Waiting: " << waitingQueue.size() << endl;
}
void ParkingLot::saveToFileOnEntry(Car car, time_t exitTime) {
    ofstream file("parking_records_entry.txt", ios::app);

    char entryT[30];

    // Format entry time
    strncpy(entryT, ctime(&car.entryTime), sizeof(entryT) - 1);
    entryT[sizeof(entryT) - 1] = '\0';

    file << "Car Number: " << car.number << "\n"
         << "Owner Name: " << car.owner << "\n"
         << "Entry Time: " << entryT
         << "--------------------------------------\n";

    file.close();
}

void ParkingLot::saveToFileOnExit(Car car, time_t exitTime, double fee) {
    ifstream infile("parking_records_entry.txt");
    if (!infile.is_open()) {
        cout << "Entry file not found!\n";
        return;
    }

    vector<string> lines;
    string line;
    bool found = false;

    // Read the entire file and check if the car exists
    while (getline(infile, line)) {
        if (line.find("Car Number: " + car.number) != string::npos) {
            found = true;
            // Skip next 2 lines (Owner Name and Entry Time) + separator
            for (int i = 0; i < 3; ++i) getline(infile, line);
        } else {
            lines.push_back(line);
        }
    }
    infile.close();

    if (!found) {
        cout << "Car not found in entry file. Cannot move to exit file.\n";
        return;
    }

    // Rewrite the entry file without the removed car
    ofstream outfile("parking_records_entry.txt");
    for (const string& l : lines) {
        outfile << l << "\n";
    }
    outfile.close();

    // Now save to exit file
    ofstream exitFile("parking_records_exit.txt", ios::app);

    char exitT[30];
    strncpy(exitT, ctime(&exitTime), sizeof(exitT) - 1);
    exitT[sizeof(exitT) - 1] = '\0';

    exitFile << "Car Number: " << car.number << "\n"
             << "Owner Name: " << car.owner << "\n"
             << "Exit  Time: " << exitT
             << "Parking Fee: Rs. " << fixed << setprecision(2) << fee << "\n"
             << "--------------------------------------\n";

    exitFile.close();

    return;
}



  

bool ParkingLot::is_empty() {
    return lane.isEmpty();
}
