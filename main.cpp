#include <iostream>

#include "Graph/Graph.h"
#include "UI/UI.h"
#include "Utils/MapParser.h"


int main() {
    std::cout << "Hello, World!" << std::endl;

    srand(time(NULL));

    Graph<coordinates> graph = parseGridMap("../maps/GridGraphs/16x16/nodes.txt", "../maps/GridGraphs/16x16/edges.txt");

//    path_t generic = graph.dijkstraShortestPath(0, 10);
//    vector<int> dfs = graph.dfs(9);
//    vector<int> dij = graph.dijkstraShortestPath(0, );
//    vector<int> astar = graph.astarShortestPath(0, 42);
    vector<int> POIs = {90, 162, 147, 200, 280, 40, 55, 180, 60, 73};
//    vector<int> nearest = graph.find_n_nearest(20, POIs, 3);
//    int near = graph.find_nearest(9, POIs);
    vector<int> ord;
    Path path;
    vector<int> nns = graph.nearestNeighborsSearch(0, 8, POIs, ord, path);
    Path twop = graph.twoOpt(nns, path);

    ord.clear();
    POIs = {90, 162, 147, 200, 280, 40, 55, 180, 60, 73};
    path = Path();
    vector<int> rnns1 = graph.RNNeighborsSearch(0, 8, POIs, ord, path, 3);
    Path rtwop = graph.twoOpt(rnns1, path);
//    ord.clear();
//    POIs = {16, 24, 10, 22, 2, 9};
//    vector<int> rnns2 = graph.RNNeighborsSearch(0, 8, POIs, ord, 2);

//    vector<vector<int>> tarjan = graph.tarjan(0);
    int i=0;

    UI ui = UI(graph, 800, 800);
    ui.showPath(path.getPath());
//    ui.showGraph();

#ifndef linux
    char c = getchar();
#endif

    return 0;
}
