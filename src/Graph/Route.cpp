#include "Route.h"

Route::Route() : weight(0), route() {}

Route::Route(double weight, const vector<deliverypoint> &route) : weight(weight), route(route) {}

double Route::getWeight() {
    return weight;
}

vector<deliverypoint> Route::getRoute() const {
    return route;
}

vector<int> Route::getRoutePOIs() const {
    vector<int> POIs;
    for (auto dp : route) {
        POIs.push_back(dp.first);
    }
    return POIs;
}

void Route::addDeliverypoint(const deliverypoint &dp) {
    route.push_back(dp);
    weight += dp.second;
}

const string &Route::getTruck() const {
    return truck;
}

void Route::setTruck(const string &truck) {
    Route::truck = truck;
}
