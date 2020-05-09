#ifndef PROJ_MAPPARSER_H
#define PROJ_MAPPARSER_H

#include <string>
#include <fstream>
#include <sstream>

#include "../Graph/Graph.h"
#include "Utils.h"

using namespace std;

Graph<coordinates> parseGridMap(const string &nodes_file, const string &edges_file);

#endif //PROJ_MAPPARSER_H
