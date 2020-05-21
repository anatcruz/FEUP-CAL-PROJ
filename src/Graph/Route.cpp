#include "Route.h"

Route::Route() : weight(0), route() {}

Route::Route(double weight, const vector<deliverypoint> &route) : weight(weight), route(route) {}

double Route::getWeight() {
    return weight;
}

vector<deliverypoint> Route::getRoute() const {
    return route;
}

void Route::addDeliverypoint(const deliverypoint &dp) {
    route.push_back(dp);
    weight += dp.second;
}
