// g++ -std=c++17 -Wall  *.cpp

#include "course.h"
#include "vehicle.h"
#include <string>
using std::string;
#include <iostream>
using std::cout; using std::endl;
#include "course.h"
#include "vehicle.h"
#include <string>
#include <iostream>
#include <sstream>
#include <set>
using std::set;

int main() {


    std::string const map_layout_1 = R"(
.*****
.*..F.
.S....
)";
    Course c1(map_layout_1);
    Vehicle v1('A');

    c1.AddVehicleToStart(&v1);

    Vehicle v2('B');
    // c1.AddVehicleToStart(&v1);
    c1.AddVehicleToStart(&v2);
    v1.SetBearing('W');
    v2.SetBearing('N');
    v1.MoveForward();
    v2.MoveForward();

    std::cout << "Before Return" << std::endl;
    std::cout << c1;
    int num_returned = c1.ReturnOffTrackVehiclesToStart();
    
    std::cout << "After First Return" << std::endl;
    std::cout << c1;
    
    v2.SetBearing('S');
    v1.MoveForward();
    v2.MoveForward(-1);
    v2.TurnRight();
    v2.MoveForward();
    c1.VehiclesAtFinish();

    std::cout << "After Second Move" << std::endl;
    std::cout << c1;

    num_returned = c1.ReturnOffTrackVehiclesToStart();
    cout << "Number of Vehicles Return to Start: " << num_returned << endl;
    std::cout << "After Second Return" << std::endl;
    std::cout << c1;
    
    v1.TurnRight();
    v1.MoveForward();
    v2.MoveForward();
    std::cout << "After Third Move" << std::endl;
    std::cout << c1;

    return 0;
}