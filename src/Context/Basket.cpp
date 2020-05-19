#include "Basket.h"

Basket::Basket(double weight, int client_nif, int id) {
    this->weight = weight;
    this->client_nif = client_nif;
    this->id = id;
}

double Basket::getWeight() const {
    return weight;
}

double Basket::getClientNif() const {
    return client_nif;
}

double Basket::getID() const {
    return id;
}
