#ifndef PROJ_ROUTE_H
#define PROJ_ROUTE_H

#include <vector>
#include "../Utils/Utils.h"


class Route {
    double weight;
    vector<deliverypoint> route;
public:
    Route();
    Route(double weight, const vector<deliverypoint> &route);

    double getWeight();

    vector<deliverypoint> getRoute() const;

    void addDeliverypoint(const deliverypoint &dp);
};


#endif //PROJ_ROUTE_H
