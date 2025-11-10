#include "Queue.h"

queue::queue(int size) {
    arr = new Car[size];
    qFront = 0;
    rear = 0;
    qSize = size;
}

void queue::enqueue(Car val) {
    if (rear == qSize) {
        cout << "Queue is Full" << endl;
        return;
    }
    arr[rear++] = val;
}

void queue::dequeue() {
    if (qFront == rear) {
        cout << "Queue is empty!" << endl;
        return;
    }
    arr[qFront] = Car();
    qFront++;
    if (qFront == rear)
        qFront = rear = 0;
}

Car queue::front() {
    if (qFront == rear) {
        cout << "Queue is empty!" << endl;
        return Car();
    }
    return arr[qFront];
}

int queue::size() { return rear - qFront; }
int queue::Maxsize(){return qSize;}
bool queue::isEmpty() { return qFront == rear; }
