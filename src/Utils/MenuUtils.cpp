#include "MenuUtils.h"

void dijkstra(Graph<coordinates> &graph, UI &ui) {
    int id_src, id_dest;
    getOption(id_src, "Source node ID: ");
    getOption(id_dest, "Destination node ID: ");

    auto start = high_resolution_clock::now();
    Path path = graph.dijkstraShortestPath(id_src, id_dest);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Size: " << path.getLength() << endl;
    cout << "Time to pathfind: " << duration.count() << endl;

    ui.showPath(path.getPath());
}

void astar(Graph<coordinates> &graph, UI &ui) {
    int id_src, id_dest;
    getOption(id_src, "Source node ID: ");
    getOption(id_dest, "Destination node ID: ");

    auto start = high_resolution_clock::now();
    Path path = graph.astarShortestPath(id_src, id_dest);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Size: " << path.getLength() << endl;
    cout << "Time to pathfind: " << duration.count() << endl;

    ui.showPath(path.getPath());
}
