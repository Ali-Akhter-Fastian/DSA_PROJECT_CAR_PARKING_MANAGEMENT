#ifndef CAR_H
#define CAR_H

#include <string>
#include <ctime>
using namespace std;

struct Car {
    string number;
    string owner;
    time_t entryTime;
};

#endif
