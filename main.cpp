#include <iostream>

#include "src/Graph.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Graph<int> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addEdge(1, 2, 1);
    graph.addEdge(2, 3, 1);
    graph.addEdge(3, 1, 1);

    return 0;
}
