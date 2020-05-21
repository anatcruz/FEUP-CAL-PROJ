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

void showClientList(Farm &farm) {
    line(20);
    cout << "Clients" << endl;
    line(20);
    for (const auto& cb_pair : farm.getClients()) {
        vector<Basket> baskets = farm.getBaskets()[cb_pair.first];
        double total = 0;
        for (Basket b: baskets){
            total += b.getWeight();
        }
        cout << "NIF: " << cb_pair.first << " | Node ID: " << cb_pair.second.getClientNodeID() << " | Baskets total weight: " << total << endl;
    }
    line(20);
}

void solveTSPRoute(Graph<coordinates> &graph, UI &ui, const int &start_node, const int &end_node, vector<int> &POIs) {
    function<Path ()> tsp_algorithm;
    Path path;
    vector<int> ord;
    bool cancel = false;

    Menu algorithmSelector("Select algorithm", false);
    algorithmSelector.addOption("Cancel", [&](){ cancel = true; });
    algorithmSelector.addOption("Nearest-neighbor", [&](){ tsp_algorithm = [&](){ return graph.nearestNeighborsSearch(start_node, end_node, POIs, ord, path); }; });
    algorithmSelector.addOption("Nearest-neighbor 2-opt", [&](){ tsp_algorithm = [&](){ graph.nearestNeighborsSearch(start_node, end_node, POIs, ord, path); return graph.twoOpt(ord, path); }; });
    algorithmSelector.addOption("Randomized NN", [&](){ tsp_algorithm = [&](){ return graph.RNNeighborsSearch(start_node, end_node, POIs, ord, path, 3); }; });
    algorithmSelector.addOption("Randomized NN 2-opt", [&](){ tsp_algorithm = [&](){ graph.RNNeighborsSearch(start_node, end_node, POIs, ord, path, 3); return graph.twoOpt(ord, path); }; });
    algorithmSelector.start();
    if (cancel) { return; }

    auto start = high_resolution_clock::now();
    path = tsp_algorithm();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Size: " << path.getLength() << endl;
    cout << "Time to pathfind: " << duration.count() << endl;

    Menu showMenu("Show graph?", false);
    showMenu.addOption("No", EXIT);
    showMenu.addOption("Yes", [&](){ ui.showPath(path.getPath()); });
    showMenu.start();
}

void solveTSPwithContext(Graph<coordinates> &graph, UI &ui, Farm &farm) {
    int total_baskets = 0;
    int start_node = farm.getFarmNodeID(), end_node = farm.getGarageNodeID();
    vector<int> POIs;

    for (const auto& cb_pair : farm.getBaskets()) {
        POIs.push_back(farm.getClients()[cb_pair.first].getClientNodeID());
        total_baskets += cb_pair.second.size();
    }

    cout << "Visiting " << farm.getBaskets().size() << " nodes to deliver " << total_baskets << " baskets." << endl;

    solveTSPRoute(graph, ui, start_node, end_node, POIs);
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
