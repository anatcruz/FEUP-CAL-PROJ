#include "Client.h"

Client::Client(coordinates clientCoords, int nif) {
    this->clientCoords = clientCoords;
    this->nif = nif;
}

coordinates Client::getCoords() const {
    return coordinates();
}

int Client::getNif() const {
    return nif;
}
