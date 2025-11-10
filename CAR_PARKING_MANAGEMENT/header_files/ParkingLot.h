#ifndef PARKINGLOT_H
#define PARKINGLOT_H

#include "Car.h"
#include "Stack.h"
#include "Queue.h"

class ParkingLot {
private:
    int capacity;
    Stack lane;
    Stack tempStack;
    queue waitingQueue;

public:
    ParkingLot(int c);
    void parkCar(Car car);
    void removeCar(string number);
    void displayStatus();
};

#endif
