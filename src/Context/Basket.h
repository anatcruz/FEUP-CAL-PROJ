#ifndef PROJ_BASKET_H
#define PROJ_BASKET_H

class Basket {
private:
    double weight;
    int client_nif;
    int id;

public:
    Basket(double weight, int client_nif, int id);
    double getWeight() const;
    double getClientNif() const;
    double getID() const;
};


#endif //PROJ_BASKET_H
