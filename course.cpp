#include <string>
using std::string;
#include <iostream>
using std::ostream; using std::endl; using std::cout;
#include <sstream>
using std::ostringstream; using std::istringstream;
#include <algorithm>
using std::count_if; using std::copy_if; using std::distance;
using std::find; using std::copy;
#include <cctype>
#include <vector>
using std::vector;
#include<iterator>
#include <utility>
using std::make_pair; using std::pair;

#include "course.h"

// MISCELLANOUS FUNCTIONS //

string clean(const string &s) {
    // handles whitespace for string constructor //

    string result = s; 
    auto space = [] (char ch) {return !(isspace(ch));};
    auto it = copy_if(s.begin(), s.end(), result.begin(), space);
    result.resize(distance(result.begin(), it));
    return result;
}

// CONSTRUCTORS //

Course::Course(string input) {
    istringstream iss;
    iss.str(input);
    string line;
    int height = 0;
    int width = 0;

    // make a vector or vector<char> to represent the track //
    while(getline(iss, line)) {
        if (line == "") {
            continue;
        }
        line = clean(line);
        vector<char> current;
        width = 0;
        for(char ch : line) {
            current.push_back(ch);
            width++;
        }
        track.push_back(current);
        height++;
    }

    // initialize data members //
    og_track = track;
    start = (*this).FindStartAndFinish('S');
    finish = (*this).FindStartAndFinish('F');
    dimensions = make_pair(height, width);
    off_track = (*this).FindOffTrack();
}

Course::Course(Course const & c) {
    track = c.og_track;
    og_track = c.og_track;
    start = c.start;
    finish = c.finish;
    dimensions = c.dimensions;
}

// PRIVATE MEMBER FUNCTIONS //

pair<int, int> Course::FindStartAndFinish(char s_or_f) {
    // find the coordinates of 'S' or 'F' in the track //

    int line = 0;
    int position = 0;
    bool found = false;

    for(auto v : track) {
        position = 0;
        for(char ch : v) {
            if (ch == s_or_f) {
                found = true;
                break;
            }
            position++;
        }
        if (found == true) {
            break;
        }
        line++;
    }
    return make_pair(line, position);
}

void Course::UpdateCourse() {
    // resets track, then updates positions of vehicles for output //

    track = og_track;
    for(auto v : cars) {
        track[(*v).position.first][(*v).position.second] = (*v).token;
    }
}

vector<pair<int, int>> Course::FindOffTrack() {
    // compiles vector of off_track coordinates //

    int row = 0;
    int column = 0;
    vector<pair<int, int>> off_track;

    for(auto v : og_track) {
        column = 0;
        for (auto ch : v) {
            if(ch == '.') {
                off_track.push_back(make_pair(row, column));
            }
            column++;
        }
        row++;
    }
    return off_track;
}

// OPERATORS //

ostream &operator<<(ostream &out, Course & c) {
    c.UpdateCourse();
    string border((c.dimensions.second)+2, '+');

    out << border << endl;
    for (auto v : c.track) {
        out << "+";
        for (char ch : v) {
            out << ch;
        }
        out << "+" << endl;
    }
    out << border << endl;

    return out;
}

Course &Course::operator=(Course & c) {
    // assigns the lhs with the track and vehicles with the rhs info //
    // clears the track and vehicles from the rhs                    //

    track = c.og_track;
    og_track = c.og_track;
    cars = c.cars;
    start = c.start;
    finish = c.finish;
    dimensions = c.dimensions;
    off_track = c.off_track;

    (*this).UpdateCourse();

    c.track = c.og_track;
    (c.cars).clear();

    return *this;
}

// PUBLIC MEMBER FUNCTIONS //

void Course::AddVehicleToStart(Vehicle * v) {
    // adds a vehicle to the course //

    cars.push_back(v);
    (*v).position = start;
    (*this).UpdateCourse();
}

set<Vehicle> Course::VehiclesAtFinish() {
    set<Vehicle> finish_line;
    for(auto v : cars) {
        if(((*v).position) == finish) {
            // if the vehicle's coordinates matches the finish position //

            finish_line.insert(*v);
        }
    }

    return finish_line;
}

int Course::ReturnOffTrackVehiclesToStart(){
    int returned = 0;
    for (auto v : cars) {
        if((*v).position.first >= dimensions.first || (*v).position.first < 0) {
            // if off course to the left or right //

            (*v).position = start;
            returned++;
        }
        else if ((*v).position.second >= dimensions.second || (*v).position.second < 0) {
            // if off course above or below //

            (*v).position = start;
            returned++;
        }
        else {
            for(pair<int, int> coord : off_track) {
                if ( (*v).position == coord) {
                    // if on an off track coordinate //

                    (*v).position = start;
                    returned++;
                }
            }
        }
    }
    (*this).UpdateCourse();
    return returned;
}
