#pragma once

#include <string>
using std::string;
#include <iostream>
using std::ostream;
#include <vector>
using std::vector;
#include <algorithm>
using std::find;
#include <utility>
using std::pair;
#include <set>
using std::set;

#include "vehicle.h"

class Course {
    private:

    // private data members //
    vector<vector<char>> track;
    vector<vector<char>> og_track;
    vector<Vehicle *> cars;
    pair<int, int> start;
    pair<int, int> finish;
    pair<int, int> dimensions;
    vector<pair<int, int>> off_track;
    // coordinates of vehicles are represented as a pair //
    // pair<row, column> within the track                //

    // private member functions //
    pair<int, int> FindStartAndFinish(char);    // finds coordinate of start/finish
    void UpdateCourse();                        // updates vehicles' postions on track
    vector<pair<int, int>> FindOffTrack();      // list of off track coordinates

    public:

    // constructors //
    Course() = default;
    Course(string);
    Course(Course const &);

    // overloaded operators //
    Course &operator=(Course &);
    friend ostream &operator<<(ostream &, Course &);

    // member functions //
    void AddVehicleToStart(Vehicle *);      // places vehicle at start and adds to vector
    set<Vehicle> VehiclesAtFinish();        // set of vehicles at the finish position
    int ReturnOffTrackVehiclesToStart();    // updates off track vehicle's position

};

ostream &operator<<(ostream &, Course &);
