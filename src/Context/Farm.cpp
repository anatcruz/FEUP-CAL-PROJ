#include "Farm.h"


Farm::Farm(int farmNodeID) {
    this->farmNodeID = farmNodeID;
}

int Farm::getFarmNodeID() const {
    return farmNodeID;
}

vector<Basket> Farm::getBaskets() {
    return baskets;
}

void Farm::addBasket(Basket basket) {
    baskets.push_back(basket);
}
