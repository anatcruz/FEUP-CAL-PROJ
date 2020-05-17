#ifndef PROJ_PERFORMANCETESTING_H
#define PROJ_PERFORMANCETESTING_H

#include <iostream>
#include <algorithm>
#include <limits>
#include <chrono>
#include "../Graph/Graph.h"
#include "Utils.h"

using namespace std;
using namespace std::chrono;

void dijkstraPerfTest(Graph<coordinates> &graph);

void astarPerfTest(Graph<coordinates> &graph);

#endif //PROJ_PERFORMANCETESTING_H
