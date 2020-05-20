#ifndef PROJ_FARM_H
#define PROJ_FARM_H

#include <vector>
#include "Utils/Utils.h"
#include "Basket.h"

class Farm {
private:
    int farmNodeID;
    vector<Basket> baskets;
public:
    Farm(int farmNodeID);
    int getFarmNodeID() const;
    vector<Basket> getBaskets();
    void addBasket(Basket basket);
};


#endif //PROJ_FARM_H
