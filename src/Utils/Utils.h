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

#endif //PROJ_UTILS_H
