#include "Farm.h"


Farm::Farm(coordinates farmCoords) {
    this->farmCoords = farmCoords;
}

coordinates Farm::getFarmCoords() const {
    return farmCoords;
}
