#include "Truck.h"

Truck::Truck(string plate) {
    this->capacity = INFINITY;
    this->plate = plate;
}

Truck::Truck(double capacity, string plate) {
    this->capacity = capacity;
    this->plate = plate;
}

void Truck::setCapacity(double capacity) {
    this->capacity = capacity;
}

double Truck::getCapacity() const {
    return capacity;
}

string Truck::getPlate() const {
    return plate;
}