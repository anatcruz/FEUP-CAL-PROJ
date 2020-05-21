#ifndef PROJ_TRUCK_H
#define PROJ_TRUCK_H

#include "Utils/Utils.h"

class Truck {
private:
    double capacity;
    string plate;
public:
    Truck(string plate);
    Truck(double capacity, string plate);
    double getCapacity() const;
    string getPlate() const;
};


#endif //PROJ_TRUCK_H
