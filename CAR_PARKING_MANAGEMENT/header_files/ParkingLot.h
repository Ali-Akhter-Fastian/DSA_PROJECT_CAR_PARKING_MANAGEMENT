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
    double removeCar(string number);
    void displayStatus();
    bool is_empty();
    double calculateFee(time_t entry, time_t exit);
    void saveToFileOnEntry(Car car,  time_t exitTime);
    void saveToFileOnExit(Car car,  time_t exitTime, double fee);
};
#endif
