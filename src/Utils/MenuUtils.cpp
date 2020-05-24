#include "MenuUtils.h"

void loadGraph(Graph<coordinates> &graph, Farm &farm, vector<int> &last_path, const string &nodes_file, const string &edges_file, bool grid) {
    graph = parseMap(nodes_file, edges_file, grid);
    farm = Farm();
    last_path.clear();
}

void loadGraph(Graph<coordinates> &graph, Farm &farm, vector<int> &last_path, const string &nodes_file, const string &edges_file, bool grid, const string &farm_file, const string &clients_file) {
    graph = parseMap(nodes_file, edges_file, grid);
    farm = loadContext(graph, farm_file, clients_file);
    last_path.clear();
}

void shortestPath(Graph<coordinates> &graph, UI &ui, const function<Path (int, int)> &spAlgorithm) {
    int id_src, id_dest;
    getOption(id_src, "Source node ID: ", [&](int a) { return graph.isValidID(a); });
    getOption(id_dest, "Destination node ID: ", [&](int a) { return graph.isValidID(a); });

    auto start = high_resolution_clock::now();
    Path path = spAlgorithm(id_src, id_dest);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Size: " << path.getLength() << endl;
    cout << "Time to pathfind: " << duration.count() << endl;

    Menu showMenu("Show path?", false);
    showMenu.addOption("No", EXIT);
    showMenu.addOption("Yes", [&](){ ui.showPath(path.getPath()); });
    showMenu.start();
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

    Menu showMenu("Show path?", false);
    showMenu.addOption("No", EXIT);
    showMenu.addOption("Yes", [&](){ ui.showDeliveryPath(path.getPath(), ord); });
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

void solveTSPnoContext(Graph<coordinates> &graph, UI &ui) {
    vector<int> POIs;
    int start_node, end_node;

    getOption(start_node, "Source node ID: ", [&](int a) { return graph.isValidID(a); });
    getOption(end_node, "Destination node ID: ", [&](int a) { return graph.isValidID(a); });
    getOptionList(POIs, "Node to visit: ", [&](int a) { return graph.isValidID(a); });

    cout << "Visiting " << POIs.size() << " nodes." << endl;

    solveTSPRoute(graph, ui, start_node, end_node, POIs);
}

void solveVRPsweep(Graph<coordinates> &graph, UI &ui, Farm &farm) {
    int total_baskets = 0;
    double total_weight = 0;
    vector<deliverypoint> POIs;

    for (const auto& cb_pair : farm.getBaskets()) {
        double weight = 0;
        for (auto basket : cb_pair.second) {
            weight += basket.getWeight();
        }
        POIs.emplace_back(farm.getClients()[cb_pair.first].getClientNodeID(), weight);
        total_baskets += cb_pair.second.size();
        total_weight += weight;
    }

    cout << "Visiting " << farm.getBaskets().size() << " nodes to deliver " << total_baskets << " baskets with a total weight of " << total_weight << endl;

    vector<Route> routes = graph.sweep(farm.getFarmNodeID(), farm.getCapacities(), POIs);

    cout << "Calculated " << routes.size() << " routes to fulfill deliveries." << endl;

    for (auto &route : routes) {
        vector<int> routePOIs = route.getRoutePOIs();
        solveTSPRoute(graph, ui, farm.getFarmNodeID(), farm.getGarageNodeID(), routePOIs);
    }
}

vector<int> largestSCC(Graph<coordinates> &graph, UI &ui) {
    auto start = high_resolution_clock::now();
    vector<vector<int>> scc_list = graph.tarjan(0);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time: " << duration.count() << endl;
    cout << "Total number of strongly connected components: " << scc_list.size() << endl;

    auto largest = max_element(scc_list.begin(), scc_list.end(), [&](vector<int> &scc1, vector<int> &scc2) { return scc1.size() < scc2.size(); });

    cout << "Largest SCC size: " << largest->size();

    Menu showMenu("Show largest SCC?", false);
    showMenu.addOption("No", EXIT);
    showMenu.addOption("Yes", [&](){ ui.showPath(*largest); });
    showMenu.start();

    return *largest;
}

bool isContextLoaded(Farm &farm){
    if(farm.getFarmNodeID() == -1){
        cinERR("No context loaded! Please load a graph with problem context before accessing this functionality.");
        enterWait();
        return false;
    }
    return true;
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
    enterWait();
}

void showBasketList(Farm &farm){
    line(20);
    cout << "Baskets" << endl;
    line(20);
    for (const auto& cb_pair : farm.getBaskets()) {
        vector<Basket> baskets = cb_pair.second;
        for (Basket b: baskets){
            cout << "Client's NIF: " << cb_pair.first << " | Weight: " << b.getWeight() << endl;
        }
    }
    line(20);
    enterWait();
}

void showTruckList(Farm &farm){
    line(20);
    cout << "Baskets" << endl;
    line(20);
    for (Truck t: farm.getTrucks()) {
        cout << "Truck's plate: " << t.getPlate() << " | Capacity: " << t.getCapacity() << endl;
    }
    line(20);
    enterWait();
}

