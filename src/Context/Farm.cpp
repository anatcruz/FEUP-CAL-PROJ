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

/**Auxiliar Functions for Deliveries**/
bool Farm::searchClientByNIF(int nif){
    return clients.find(nif) != clients.end();
}

void Farm::createClient(Graph<coordinates> &graph) {
    int nif, nodeID;

    getOption(nif, "Enter new client's nif: ");
    if(searchClientByNIF(nif)){
        cinERR("ERROR: It already exits a client with the given nif!");
        enterWait();
        return;
    }

    getOption(nodeID, "Enter new client's node ID: ");
    if(!graph.isValidID(nodeID)){
        cinERR("ERROR: Invalid node ID!");
        enterWait();
        return;
    }

    auto vertex = graph.findVertex(nodeID);
    if(vertex->tag != none){
        cinERR("ERROR: Invalid node ID, already in use!");
        enterWait();
        return;
    }

    addClient(Client(nodeID, nif));
    vertex->tag = cliente;

    cout << "Client successfully created!" << endl;
    enterWait();
}

void Farm::editClient(Graph<coordinates> &graph) {
    int nif, nodeID;

    getOption(nif, "Enter new client's nif: ");
    if(!searchClientByNIF(nif)){
        cinERR("ERROR: Doesn't exits a client with the given nif!");
        enterWait();
        return;
    }

    getOption(nodeID, "Enter client's new node ID: ");
    if(!graph.isValidID(nodeID)){
        cinERR("ERROR: Invalid node ID!");
        enterWait();
        return;
    }

    auto vertex = graph.findVertex(nodeID);
    if(vertex->tag != none){
        cinERR("ERROR: Invalid node ID, already in use!");
        enterWait();
        return;
    }

    Client &client = clients.at(nif);
    if(nodeID != client.getClientNodeID()){
        vertex = graph.findVertex(client.getClientNodeID());
        vertex->tag = none;

        client.setClientNodeID(nodeID);
        vertex = graph.findVertex(nodeID);
        vertex->tag = cliente;
    }

    cout << "Client successfully edited!" << endl;
    enterWait();
}

void Farm::removeClient(Graph<coordinates> &graph) {
    int nif;
    getOption(nif, "Enter new client's nif: ");
    if(!searchClientByNIF(nif)){
        cinERR("ERROR: Doesn't exits a client with the given nif!");
        enterWait();
        return;
    }

    auto vertex = graph.findVertex(clients.at(nif).getClientNodeID());
    vertex->tag = none;

    clients.erase(nif);
    baskets.erase(nif);

    cout << "Client and corresponding baskets successfully removed!" << endl;
    enterWait();
}


void Farm::createBasket() {
    int nif;
    double weight;

    getOption(nif, "Enter client's nif: ");
    if(!searchClientByNIF(nif)){
        cinERR("ERROR: Doesn't exits a client with the given nif, please create a new one!");
        enterWait();
        return;
    }

    getDouble(weight, "Enter basket weight: ");

    addBasket(Basket(weight, nif));

    cout << "Basket successfully created!" << endl;
    enterWait();
}
//TODO add editBasket and removeBasket

//TODO Maybe change return value to a pointer, for use in editTruck and removeTruck
bool Farm::searchTruckByPlate(string plate) {
    for(Truck t: trucks){
        if(t.getPlate() == plate) return true;
    }
    return false;
}


void Farm::createTruck() {
    string plate;
    double capacity;

    cout << "Enter new truck's plate: ";
    getline(cin, plate);
    if(searchTruckByPlate(plate)){
        cinERR("ERROR: It already exits a truck with the given plate!");
        enterWait();
        return;
    }

    getDouble(capacity, "Enter truck's capacity: ");

    addTruck(Truck(capacity, plate));

    cout << "Truck successfully created!" << endl;
    enterWait();
}

void Farm::editTruck() {
    string plate;
    double capacity;

    cout << "Enter truck's plate: ";
    getline(cin, plate);
    if(!searchTruckByPlate(plate)){
        cinERR("ERROR: It doesn't exit a truck with the given plate!");
        enterWait();
        return;
    }

    getDouble(capacity, "Enter truck's new capacity: ");

    for(auto &truck : trucks){
        if(truck.getPlate() == plate){
            truck.setCapacity(capacity);
            break;
        }
    }

    cout << "Truck successfully edited!" << endl;
    enterWait();
}

void Farm::removeTruck() {
    string plate;
    double capacity;

    cout << "Enter truck's plate: ";
    getline(cin, plate);
    if(!searchTruckByPlate(plate)){
        cinERR("ERROR: It doesn't exit a truck with the given plate!");
        enterWait();
        return;
    }

    for(auto it=trucks.begin(); it!=trucks.end(); it++){
        if((*it).getPlate() == plate){
            trucks.erase(it);
            break;
        }
    }

    cout << "Truck successfully removed!" << endl;
    enterWait();
}
