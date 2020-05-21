#ifndef PROJ_UTILS_H
#define PROJ_UTILS_H

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <functional>
#include <vector>

using namespace std;

typedef pair<double, double> coordinates;

void line(int size, char ch = '-');

void cinERR(const string &message);

void getOption(int &dest, const string &message = "Option: ");

void getOptionList(vector<int> &dest, const string &message = "Option (* to end): ", function<bool(int)> cond = [](int a) { return true; });

double euclidianDistance(pair<double, double> point1, pair<double, double> point2);

vector<int> removeIdFromVector(vector<int> v, int id);

void enterWait(const string &message = "ENTER to go back");

#endif //PROJ_UTILS_H
