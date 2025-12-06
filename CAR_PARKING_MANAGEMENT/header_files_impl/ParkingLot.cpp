#include "ParkingLot.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>

using namespace std;

ParkingLot::ParkingLot(int c) : lane(c), tempStack(c), waitingQueue(c), capacity(c) {}

void ParkingLot::parkCar(Car car) {
     car.entryTime = time(0);
    if (lane.getSizeOfLot() < capacity) {
        lane.push(car);
        cout << "Car \"" << car.number << "\" parked successfully.\n";
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
    saveToFile(removedCar, fee, exitTime);

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
void ParkingLot::saveToFile(Car car, double fee, time_t exitTime) {
    ofstream file("parking_records.txt", ios::app);

    char entryT[30], exitT[30];
    ctime_s(entryT, sizeof(entryT), &car.entryTime);
    ctime_s(exitT, sizeof(exitT), &exitTime);

    file << "Car Number: " << car.number << "\n"
         << "Owner Name: " << car.owner << "\n"
         << "Entry Time: " << entryT
         << "Exit  Time: " << exitT
         << "Parking Fee: Rs. " << fee << "\n"
         << "--------------------------------------\n";

    file.close();
}
