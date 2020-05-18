#ifndef PROJ_CLIENT_H
#define PROJ_CLIENT_H

#include "Utils/Utils.h"

class Client {
private:
    coordinates clientCoords;
    int nif;
public:
    Client(coordinates clientCoords, int nif);
    coordinates getCoords() const;
    int getNif() const;
};


#endif //PROJ_CLIENT_H
