#ifndef PROJ_FARM_H
#define PROJ_FARM_H

#include <vector>
#include <unordered_map>
#include "Utils/Utils.h"
#include "Client.h"
#include "Basket.h"

class Farm {
private:
    int farmNodeID;
    unordered_map<int, Client> clients;
    unordered_map<int,vector<Basket>> baskets;
public:
    Farm(int farmNodeID);
    int getFarmNodeID() const;
    unordered_map<int, vector<Basket>> getBaskets();
    void addBasket(Basket basket);

    unordered_map<int, Client> getClients();
    void addClient(Client client);
};


#endif //PROJ_FARM_H