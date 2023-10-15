#pragma once

#include <iostream>
using std::ostream;
#include <utility>
using std::pair;

class Vehicle {
    private:

    // private data members //
    pair<int, int> position = {-1,-1};
    char direction = 'N';
    
    public:
    char token = ' ';

    // constructors //
    Vehicle() = default;
    Vehicle(char);

    // overloaded operators //
    bool operator<(const Vehicle &) const;
    bool operator==(const Vehicle &) const;
    friend ostream &operator<<(ostream &, const Vehicle &);

    // member functions //
    void SetBearing(char);          // sets character direction
    void MoveForward(int i = 1);    // increments postion coordinates
    void TurnLeft();                // adjusts character direction
    void TurnRight();

    friend class Course;
};

ostream &operator<<(ostream &, const Vehicle &);