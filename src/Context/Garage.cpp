#include "Garage.h"


Garage::Garage() {
    this->garageNodeID = -1;
}

Garage::Garage(int garageNodeID) {
    this->garageNodeID = garageNodeID;
}

int Garage::getGarageNodeID() const {
    return garageNodeID;
}

vector<Truck> Garage::getTrucks() {
    return vector<Truck>();
}

void Garage::addTruck(Truck truck) {
    trucks.push_back(truck);
}
