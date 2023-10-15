#include <vector>
using std::vector;
#include <algorithm>
using std::find;
#include <stdexcept>
using std::invalid_argument;

#include "vehicle.h"
// CONNSTRUCTORS //

Vehicle::Vehicle(char ch) {
    token = ch;
}

// OPERATORS //

ostream &operator<<(ostream & out, const Vehicle & v) {
    out << v.token;

    return out;
}

bool Vehicle::operator<(const Vehicle & v) const {
    return (token < v.token);
}

bool Vehicle::operator==(const Vehicle & v) const {
    return (token == v.token);
}

// MEMBR FUNCTIONS //

void Vehicle::SetBearing(char ch) {
    vector<char> compass{'N', 'E', 'S', 'W'};
    auto it = find(compass.begin(), compass.end(), ch);
    if(it == compass.end()) {
        throw std::invalid_argument("invalid");
    }
    direction = ch;
}

void Vehicle::MoveForward(int i){
    if (direction == 'N') {
        position.first -= i;
    }
    else if (direction == 'E') {
        position.second += i;
    }
    else if (direction == 'S') {
        position.first += i;
    }
    else if (direction == 'W') {
        position.second -= i;
    }
}

void Vehicle::TurnLeft() {
    vector<char> compass{'N', 'E', 'S', 'W'};

    auto it = find(compass.begin(), compass.end(), direction);
    if ((it+4) == compass.end()) {
        direction = 'W';
    }
    else {
        direction = *(it-1);
    }
}

void Vehicle::TurnRight() {
    vector<char> compass{'N', 'E', 'S', 'W'};

    auto it = find(compass.begin(), compass.end(), direction);
    if ((it+1) == compass.end()) {
        direction = 'N';
    }
    else {
        direction = *(it+1);
    }
}
