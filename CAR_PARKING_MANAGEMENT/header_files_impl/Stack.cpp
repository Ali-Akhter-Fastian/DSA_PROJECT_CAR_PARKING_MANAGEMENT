#include "Stack.h"

Stack::Stack(int size) {
    top = -1;
    arr = new Car[size];
    this->size = size;
}

void Stack::push(Car val) {
    if (top < size - 1)
        arr[++top] = val;
    else
        cout << "Stack Overflow" << endl;
}

void Stack::pop() {
    if (top >= 0)
        top--;
    else
        cout << "Stack Underflow" << endl;
}

Car Stack::peek() {
    if (top >= 0)
        return arr[top];
    cout << "Stack is Empty" << endl;
    return Car();
}

bool Stack::isEmpty() { return top == -1; }

int Stack::getSizeOfLot() { return top + 1; }
