#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "Car.h"
using namespace std;

class Stack {
    Car* arr;
    int top;
    int size;

public:
    Stack(int size);
    void push(Car val);
    void pop();
    Car peek();
    bool isEmpty();
    int getSizeOfLot();
};

#endif
