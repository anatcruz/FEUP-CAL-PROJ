#ifndef PROJ_GARAGE_H
#define PROJ_GARAGE_H

#include <vector>
#include "Truck.h"


class Garage {
private:
    int garageNodeID;
    vector<Truck> trucks;
public:
    Garage();
    Garage(int garageNodeID);
    int getGarageNodeID() const;
    vector<Truck> getTrucks();
    void addTruck(Truck truck);
};


#endif //PROJ_GARAGE_H
