#include "MenuUtils.h"

void shortestPath(Graph<coordinates> &graph, UI &ui, const function<Path (int, int)> &spAlgorithm) {
    int id_src, id_dest;
    graph.getValidID(id_src, "Source node ID: ");
    graph.getValidID(id_dest, "Destination node ID: ");

    auto start = high_resolution_clock::now();
    Path path = spAlgorithm(id_src, id_dest);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Size: " << path.getLength() << endl;
    cout << "Time to pathfind: " << duration.count() << endl;

    ui.showPath(path.getPath());
}

void dijkstra(Graph<coordinates> &graph, UI &ui) {
    shortestPath(graph, ui, [&](int s, int d) { return graph.dijkstraShortestPath(s, d); });
}

void dijkstraBiDir(Graph<coordinates> &graph, UI &ui) {
    shortestPath(graph, ui, [&](int s, int d) { return graph.dijkstraBiDirShortestPath(s, d); });
}

void astar(Graph<coordinates> &graph, UI &ui) {
    shortestPath(graph, ui, [&](int s, int d) { return graph.astarShortestPath(s, d); });
}

void astarBiDir(Graph<coordinates> &graph, UI &ui) {
    shortestPath(graph, ui, [&](int s, int d) { return graph.astarBiDirShortestPath(s, d); });
}

vector<int> largestSCC(Graph<coordinates> &graph, UI &ui) {
    auto start = high_resolution_clock::now();
    vector<vector<int>> scc_list = graph.tarjan(0);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time: " << duration.count() << endl;

    auto largest = max_element(scc_list.begin(), scc_list.end(), [&](vector<int> &scc1, vector<int> &scc2) { return scc1.size() < scc2.size(); });

    ui.showPath(*largest);

    return *largest;
}
