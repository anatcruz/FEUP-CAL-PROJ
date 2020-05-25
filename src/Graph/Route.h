#ifndef PROJ_ROUTE_H
#define PROJ_ROUTE_H

#include <vector>
#include <string>
#include "../Utils/Utils.h"


class Route {
    double weight;
    vector<deliverypoint> route;
    string truck;
public:
    Route();
    Route(double weight, const vector<deliverypoint> &route);

    double getWeight();

    vector<deliverypoint> getRoute() const;
    vector<int> getRoutePOIs() const;

    void addDeliverypoint(const deliverypoint &dp);

    const string &getTruck() const;

    void setTruck(const string &truck);
};


#endif //PROJ_ROUTE_H
