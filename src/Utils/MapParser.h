#ifndef PROJ_MAPPARSER_H
#define PROJ_MAPPARSER_H

#include <string>
#include <fstream>
#include <sstream>

#include "../Graph/Graph.h"
#include "../Context/Farm.h"
#include "Utils.h"

using namespace std;

/**
 * Reads data from files into a coordinates graph.
 * @param grid determines if graph is a gridmap or not, used later for drawing
 * */
Graph<coordinates> parseMap(const string &nodes_file, const string &edges_file, bool grid);

/**
 * Reads data from files into Farm class.
 * */
Farm loadContext(Graph<coordinates> &graph, const string &farm_file, const string &clients_file);

/**
 * Saves changes made to a Farm object to farm files.
 * */
void saveFarmChanges(Farm &farm);

#endif //PROJ_MAPPARSER_H
