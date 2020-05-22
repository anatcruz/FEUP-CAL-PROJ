#ifndef PROJ_BASKET_H
#define PROJ_BASKET_H

class Basket {
private:
    double weight;
    int client_nif;
public:
    Basket(double weight, int client_nif);
    void setWeight(double weight);
    double getWeight() const;
    double getClientNif() const;
};


#endif //PROJ_BASKET_H
