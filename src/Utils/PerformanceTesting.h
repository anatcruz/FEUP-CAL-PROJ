#ifndef PROJ_PERFORMANCETESTING_H
#define PROJ_PERFORMANCETESTING_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <chrono>
#include <functional>
#include "../Graph/Graph.h"
#include "Utils.h"

using namespace std;
using namespace std::chrono;

/**
 * Functions that run an algorithm several times and calculate statistics
 * about it's time performance.
 * */

void dijkstraPerfTest(Graph<coordinates> &graph);

void dijkstraBiDirPerfTest(Graph<coordinates> &graph);

void astarPerfTest(Graph<coordinates> &graph);

void astarBiDirPerfTest(Graph<coordinates> &graph);

void tarjanPerfTest(Graph<coordinates> &graph);

#endif //PROJ_PERFORMANCETESTING_H
