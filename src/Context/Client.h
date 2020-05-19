#ifndef PROJ_CLIENT_H
#define PROJ_CLIENT_H

#include "Utils/Utils.h"

class Client {
private:
    int clientNodeID;
    int nif;

public:
    Client(int clientNodeID, int nif);
    int getClientNodeID() const;
    int getNif() const;
};


#endif //PROJ_CLIENT_H
