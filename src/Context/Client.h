#ifndef PROJ_CLIENT_H
#define PROJ_CLIENT_H

#include "Utils/Utils.h"

class Client {
private:
    int clientNodeID;
    int nif;
public:
    Client();
    Client(int clientNodeID, int nif);
    void setClientNodeID(int nodeID);
    int getClientNodeID() const;
    int getNif() const;
};


#endif //PROJ_CLIENT_H
