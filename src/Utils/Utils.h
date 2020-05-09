#ifndef PROJ_UTILS_H
#define PROJ_UTILS_H

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

void line(int size, char ch = '-');

void cinERR(const string &message);

void getOption(int &dest, const string &message = "Option: ");

double euclidianDistance(pair<double, double> point1, pair<double, double> point2);

#endif //PROJ_UTILS_H
