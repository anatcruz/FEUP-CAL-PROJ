#include <iostream>

#include "Graph/Graph.h"
#include "UI/UI.h"
#include "Utils/MapParser.h"


int main() {
    std::cout << "Hello, World!" << std::endl;

    Graph<coordinates> graph = parseGridMap("../maps/GridGraphs/16x16/nodes.txt", "../maps/GridGraphs/16x16/edges.txt");

    vector<int> dfs = graph.dfs(9);
    vector<int> dij = graph.dijkstraShortestPath(0, 42);
    vector<int> astar = graph.astarShortestPath(0, 42, euclidianDistance);
    int i=0;

    UI ui = UI(graph, 400, 400);
    ui.showPath(astar);

    char c = getchar();

    return 0;
}
