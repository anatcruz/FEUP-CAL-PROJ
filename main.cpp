#include <iostream>

#include "Graph/Graph.h"
#include "UI/UI.h"
#include "Utils/MapParser.h"


int main() {
    std::cout << "Hello, World!" << std::endl;

    Graph<coordinates> graph = parseGridMap("../maps/GridGraphs/4x4/nodes.txt", "../maps/GridGraphs/4x4/edges.txt");

    vector<int> dfs = graph.dfs(9);
    vector<int> dij = graph.dijkstraShortestPath(1, 6);
    int i=0;

    UI ui = UI(graph, 400, 400);
    ui.showGraph();
    getchar();
    return 0;
}
