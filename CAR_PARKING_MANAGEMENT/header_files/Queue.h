#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "Car.h"
using namespace std;

class queue {
    Car* arr;
    int qSize;
    int qFront;
    int rear;

public:
    queue(int size);
    void enqueue(Car val);
    void dequeue();
    Car front();
    int size();
    bool isEmpty();
};

#endif
