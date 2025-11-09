#include<iostream>
using namespace std;

struct Car {
    string number;
    string owner;
    time_t entryTime;
};

class Stack {
    Car* arr;
    int top;
    int size;

public:
    Stack(int size) {
        top = -1;
        arr = new Car[size];
        this->size = size;
    }

    void push(Car val) {
        if (top < size - 1) {
            top++;
            arr[top] = val;
        } else {
            cout << "Stack Overflow" << endl;
        }
    }

    void pop() {
        if (top >= 0) {
            top--;
        } else {
            cout << "Stack Underflow" << endl;
        }
    }

    Car peek() {
        if (top >= 0) {
            return arr[top];
        } else {
            cout << "Stack is Empty" << endl;
            return Car();
        }
    }

    bool isEmpty() {
        return top == -1;
    }

    int getSizeOfLot() {
        return top + 1;
    }
};

class queue {
    Car* arr;
    int qSize;
    int qFront;
    int rear;

public:
    queue(int size) {
        arr = new Car[size];
        qFront = 0;
        rear = 0;
        qSize = size;
    }

    void enqueue(Car val) {
        if (rear == qSize) {
            cout << "Queue is Full" << endl;
            return;
        }
        arr[rear] = val;
        rear++;
    }

    void dequeue() {
        if (qFront == rear) {
            cout << "Queue is empty!" << endl;
            return;
        }
        arr[qFront] = Car();
        qFront++;
        if (qFront == rear) {
            qFront = 0;
            rear = 0;
        }
    }

    Car front() {
        if (qFront == rear) {
            cout << "Queue is empty!" << endl;
            return Car();
        }
        return arr[qFront];
    }

    Car back(){
        if (qFront == rear)
        {
            cout<<"Stack is empty!"<<endl;
            return Car();
            
        }
        
        return arr[rear-1];
    }

    int size(){
        return qSize;
    }

    bool isEmpty() {
        return qFront == rear;
    }
};

class ParkingLot {
private:
    int capacity;
    Stack lane;
    Stack tempStack;
    queue waitingQueue;

public:
    ParkingLot(int c) : lane(c), tempStack(c), waitingQueue(c), capacity(c) {}

    void parkCar(Car car);
    void removeCar(string number);
    void displayStatus();
    void saveToFile(Car car, double fee);
    double calculateFee(time_t entry, time_t exit);
};

// ---

// 🔧 Function Implementations

// 🅰 Park Car

void ParkingLot::parkCar(Car car) {
    if (lane.getSizeOfLot() < capacity) {
        lane.push(car);
        cout << "Car \"" << car.number << "\" parked successfully.\n";
    } else {
        cout << "Parking full. Added to waiting queue.\n";
        waitingQueue.enqueue(car);
    }
}


// ---

// 🅱 Remove Car

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
//FUNCTION TO DISPLAY PARKING LOT OCCUPIED SPACE, EMPTY SPACE, WAITING CARS
void ParkingLot::displayStatus() {
    cout << "\n--- Parking Status ---\n";
    cout << "Total Capacity: " << capacity << endl;
    cout << "Occupied: " << lane.getSizeOfLot() << endl;
    cout << "Waiting: " << waitingQueue.size() << endl;
}

int main() {
    ParkingLot lot(3);
    int choice;

    do {
        cout << "\n1. Park Car\n2. Remove Car\n3. Display Status\n4. Exit\nChoice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        if (choice == 1) {
            Car c;
            cout << "Enter car number: ";
            getline(cin, c.number); 

            cout << "Enter owner name: ";
            getline(cin, c.owner);    

            lot.parkCar(c);
        } else if (choice == 2) {
            string num;
            cout << "Enter car number to remove: ";
            getline(cin, num);       
            lot.removeCar(num);
        } else if (choice == 3) {
            lot.displayStatus();
        } 
        else if (choice != 4) {
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);

    cout << "Exiting system.\n";
    return 0;
}
