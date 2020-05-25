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
#include "MapParser.h"
#include "Utils.h"

using namespace std;
using namespace std::chrono;

/**
 * Loads a context free graph, clearing all the existing context variables
 * */
void loadGraph(Graph<coordinates> &graph, Farm &farm, vector<int> &last_path, const string &nodes_file, const string &edges_file, bool grid);

/**
 * Loads a graph with context, setting context vairables accordingly.
 * */
void loadGraph(Graph<coordinates> &graph, Farm &farm, vector<int> &last_path, const string &nodes_file, const string &edges_file, bool grid, const string &farm_file, const string &clients_file);

/**
 * The following 4 functions all ask for node input for calculating a
 * shortest path between two nodes using different algorithms.
 * */
void dijkstra(Graph<coordinates> &graph, UI &ui);

void dijkstraBiDir(Graph<coordinates> &graph, UI &ui);

void astar(Graph<coordinates> &graph, UI &ui);

void astarBiDir(Graph<coordinates> &graph, UI &ui);

/**
 * Solves an instance of the TSP using the context data (baskets and client nodes).
 * */
void solveTSPwithContext(Graph<coordinates> &graph, UI &ui, Farm &farm);

/**
 * Solves an instance of the TSP asking the user to input a list of nodes to visit/
 * */
void solveTSPnoContext(Graph<coordinates> &graph, UI &ui);

/**
 * Solves an instance of the HVRP, using the context data (baskets, client nodes and trucks).
 * */
void solveVRPsweep(Graph<coordinates> &graph, UI &ui, Farm &farm);

/**
 * Uses Tarjan's algorithm to calculate all the SCCs in the graph and returns the largest one.
 * */
vector<int> largestSCC(Graph<coordinates> &graph, UI &ui);

/**
 * Checks if a context has been loaded to prevent usage of context dependent functions otherwise.
 * */
bool isContextLoaded(Farm &farm);

/**
 * Functions used to display context information.
 * */
void showClientList(Farm &farm);
void showBasketList(Farm &farm);
void showTruckList(Farm &farm);

#endif //PROJ_MENUUTILS_H
