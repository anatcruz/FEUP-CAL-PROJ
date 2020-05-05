#include <iostream>

#include "Graph/Graph.h"
#include "UI/UI.h"
#include "Utils/MapParser.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Graph<coordinates> graph = parseGridMap("../maps/GridGraphs/16x16/nodes.txt", "../maps/GridGraphs/16x16/edges.txt");

    UI ui = UI(graph, 400, 400);
    ui.showGraph();

    return 0;
}
