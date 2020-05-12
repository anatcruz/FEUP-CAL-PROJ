#include <iostream>

#include "Graph/Graph.h"
#include "UI/UI.h"
#include "Utils/MapParser.h"


int main() {
    std::cout << "Hello, World!" << std::endl;

    Graph<coordinates> graph = parseGridMap("../maps/GridGraphs/4x4/nodes.txt", "../maps/GridGraphs/4x4/edges.txt");

//    vector<int> dfs = graph.dfs(9);
//    vector<int> dij = graph.dijkstraShortestPath(0, );
//    vector<int> astar = graph.astarShortestPath(0, 42, euclidianDistance);
//    vector<int> POIs = {16, 24, 10, 22};
//    vector<int> nearest = graph.find_n_nearest(6, POIs, 2);
//    vector<int> ord;
//    vector<int> nns = graph.nearestNeighborsSearch(0, 8, POIs, ord); //NOT WORKING /!\

    vector<vector<int>> tarjan = graph.tarjan(0);
    int i=0;

//    UI ui = UI(graph, 800, 800);
    //ui.showPath(astar);
//    ui.showGraph();

    char c = getchar();

    return 0;
}
