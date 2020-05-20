#include "Farm.h"

Farm::Farm() {
    this->farmNodeID = -1;
}

Farm::Farm(int farmNodeID) {
    this->farmNodeID = farmNodeID;
}

int Farm::getFarmNodeID() const {
    return farmNodeID;
}

unordered_map<int, vector<Basket>> Farm::getBaskets() {
    return baskets;
}

void Farm::addBasket(Basket basket) {
    baskets[basket.getClientNif()].push_back(basket);
}

unordered_map<int, Client> Farm::getClients() {
    return clients;
}

void Farm::addClient(Client client) {
    clients[client.getNif()] = client;
}

void Farm::setGarage(Garage garage) {
    this->garage = garage;
}

Garage Farm::getGarage() {
    return garage;
}
