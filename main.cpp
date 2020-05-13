#include <iostream>

#include "Graph/Graph.h"
#include "UI/UI.h"
#include "Utils/MapParser.h"


int main() {
    std::cout << "Hello, World!" << std::endl;

    Graph<coordinates> graph = parseGridMap("../maps/GridGraphs/4x4/nodes.txt", "../maps/GridGraphs/4x4/edges.txt");

//    path_t generic = graph.dijkstraShortestPath(0, 10);
//    vector<int> dfs = graph.dfs(9);
//    vector<int> dij = graph.dijkstraShortestPath(0, );
//    vector<int> astar = graph.astarShortestPath(0, 42);
    vector<int> POIs = {16, 24, 10, 22, 2, 9};
//    vector<int> nearest = graph.find_n_nearest(20, POIs, 3);
//    int near = graph.find_nearest(9, POIs);
    vector<int> ord;
    vector<int> nns = graph.nearestNeighborsSearch(0, 8, POIs, ord);
    ord.clear();
    POIs = {16, 24, 10, 22, 2, 9};
    vector<int> rnns1 = graph.RNNeighborsSearch(0, 8, POIs, ord, 2);
    ord.clear();
    POIs = {16, 24, 10, 22, 2, 9};
    vector<int> rnns2 = graph.RNNeighborsSearch(0, 8, POIs, ord, 2);

//    vector<vector<int>> tarjan = graph.tarjan(0);
    int i=0;

    UI ui = UI(graph, 800, 800);
    //ui.showPath(astar);
    ui.showGraph();

#ifndef linux
    char c = getchar();
#endif

    return 0;
}
