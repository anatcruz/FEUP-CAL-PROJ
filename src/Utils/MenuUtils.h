#ifndef PROJ_MENUUTILS_H
#define PROJ_MENUUTILS_H

#include <iostream>
#include <algorithm>
#include <functional>
#include <chrono>
#include "../Graph/Graph.h"
#include "../Context/Farm.h"
#include "../UI/UI.h"
#include "../UI/Menu.h"
#include "Utils.h"

using namespace std;
using namespace std::chrono;

void dijkstra(Graph<coordinates> &graph, UI &ui);

void dijkstraBiDir(Graph<coordinates> &graph, UI &ui);

void astar(Graph<coordinates> &graph, UI &ui);

void astarBiDir(Graph<coordinates> &graph, UI &ui);

void showClientList(Graph<coordinates> &graph, UI &ui);

void solveTSPwithContext(Graph<coordinates> &graph, UI &ui, Farm &farm);

vector<int> largestSCC(Graph<coordinates> &graph, UI &ui);

#endif //PROJ_MENUUTILS_H
