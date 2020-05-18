#ifndef PROJ_FARM_H
#define PROJ_FARM_H

#include "Utils/Utils.h"

class Farm {
private:
    coordinates farmCoords;

public:
    Farm(coordinates farmCoords);
    coordinates getFarmCoords() const;
};


#endif //PROJ_FARM_H
