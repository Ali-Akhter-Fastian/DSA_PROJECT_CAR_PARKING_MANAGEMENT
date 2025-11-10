#include "ParkingLot.h"
#include <iostream>
using namespace std;

ParkingLot::ParkingLot(int c) : lane(c), tempStack(c), waitingQueue(c), capacity(c) {}

void ParkingLot::parkCar(Car car) {
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

void ParkingLot::removeCar(string number) {
    bool found = false;

    while (!lane.isEmpty()) {
        Car topCar = lane.peek();
        lane.pop();

        if (topCar.number == number) {
            found = true;
            cout << "Car \"" << number << "\" removed successfully.\n";
            break;
        } else {
            tempStack.push(topCar);
        }
    }

    while (!tempStack.isEmpty()) {
        lane.push(tempStack.peek());
        tempStack.pop();
    }

    if (!found)
        cout << "Car not found in parking.\n";
    else if (!waitingQueue.isEmpty()) {
        Car nextCar = waitingQueue.front();
        waitingQueue.dequeue();
        parkCar(nextCar);
    }
}

void ParkingLot::displayStatus() {
    cout << "\n--- Parking Status ---\n";
    cout << "Total Capacity: " << capacity << endl;
    cout << "Occupied: " << lane.getSizeOfLot() << endl;
    cout << "Waiting: " << waitingQueue.size() << endl;
}
bool ParkingLot::is_empty() {
    return lane.isEmpty();
}
