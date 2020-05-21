#ifndef PROJ_FARM_H
#define PROJ_FARM_H

#include <vector>
#include <unordered_map>
#include "Utils/Utils.h"
#include "Client.h"
#include "Basket.h"
#include "Truck.h"

class Farm {
private:
    string farm_file, clients_file;
    int farmNodeID;
    int garageNodeID;
    vector<Truck> trucks;
    unordered_map<int, Client> clients;
    unordered_map<int,vector<Basket>> baskets;
public:
    Farm();
    Farm(string farm_file, string clients_file);
    Farm(int farmNodeID);

    string getFarmFile();
    string getClientsFile();

    void setFarmNodeID(int nodeID);
    int getFarmNodeID() const;

    void setGarageNodeID(int nodeID);
    int getGarageNodeID() const;

    unordered_map<int, vector<Basket>> getBaskets();
    void addBasket(Basket basket);

    unordered_map<int, Client> getClients();
    void addClient(Client client);

    vector<Truck> getTrucks();
    void addTruck(Truck truck);
};


#endif //PROJ_FARM_H
