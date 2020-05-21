#include "Farm.h"

Farm::Farm() {
    this->farmNodeID = -1;
}

Farm::Farm(string farm_file, string clients_file) {
    this->farm_file = farm_file;
    this->clients_file = clients_file;
}

Farm::Farm(int farmNodeID) {
    this->farmNodeID = farmNodeID;
}

string Farm::getFarmFile() {
    return farm_file;
}

string Farm::getClientsFile() {
    return clients_file;
}

bool Farm::isFarmFileChanged() const {
    return farmFileChanged;
}

bool Farm::isClientsFileChanged() const {
    return clientsFileChanged;
}

void Farm::setFarmNodeID(int nodeID) {
    this->farmNodeID = nodeID;
}

int Farm::getFarmNodeID() const {
    return farmNodeID;
}

void Farm::setGarageNodeID(int nodeID) {
    this->garageNodeID = nodeID;
}

int Farm::getGarageNodeID() const {
    return garageNodeID;
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

vector<Truck> Farm::getTrucks() {
    return trucks;
}

vector<double> Farm::getCapacities() {
    vector<double> capacities;
    for (auto &truck : trucks) {
        capacities.push_back(truck.getCapacity());
    }
    return capacities;
}

void Farm::addTruck(Truck truck) {
    trucks.push_back(truck);
}
