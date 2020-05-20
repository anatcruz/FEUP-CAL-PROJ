#include "Client.h"

Client::Client() {
    this->nif = 0;
    this->clientNodeID = -1;
}

Client::Client(int clientNodeID, int nif) {
    this->clientNodeID = clientNodeID;
    this->nif = nif;
}

int Client::getClientNodeID() const {
    return clientNodeID;
}

int Client::getNif() const {
    return nif;
}
