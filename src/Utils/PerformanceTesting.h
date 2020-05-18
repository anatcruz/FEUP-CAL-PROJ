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

#define LOG_FILE "../log.csv"

using namespace std;
using namespace std::chrono;

void dijkstraPerfTest(Graph<coordinates> &graph);

void dijkstraBiDirPerfTest(Graph<coordinates> &graph);

void astarPerfTest(Graph<coordinates> &graph);

void astarBiDirPerfTest(Graph<coordinates> &graph);

void clearLog();

#endif //PROJ_PERFORMANCETESTING_H
