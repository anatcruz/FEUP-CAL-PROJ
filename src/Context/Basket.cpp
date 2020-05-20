#include "Basket.h"

Basket::Basket(double weight, int client_nif) {
    this->weight = weight;
    this->client_nif = client_nif;
}

double Basket::getWeight() const {
    return weight;
}

double Basket::getClientNif() const {
    return client_nif;
}
