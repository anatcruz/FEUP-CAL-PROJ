#ifndef PROJ_MAPPARSER_H
#define PROJ_MAPPARSER_H

#include <string>
#include <fstream>
#include <sstream>

#include "../Graph/Graph.h"
#include "../Context/Farm.h"
#include "Utils.h"

using namespace std;

Graph<coordinates> parseMap(const string &nodes_file, const string &edges_file, bool grid);

Farm loadContext(Graph<coordinates> &graph, const string &farm_file, const string &clients_file);

void saveFarmChanges(Farm &farm);

#endif //PROJ_MAPPARSER_H
