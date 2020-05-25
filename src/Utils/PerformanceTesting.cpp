#include "PerformanceTesting.h"

void shortestPathPerfTest(Graph<coordinates> &graph, const function<Path (int, int)> &spAlgorithm, char test) {
    int id_src, id_dest, num_iter;
    getOption(num_iter, "Number of iterations: ");

    long total = 0, min_d = LONG_MAX, max_d = 0;

    for (int i = 0; i < num_iter; i++) {
        auto map = graph.getVertexMap();
        auto iter = map.begin();
        advance(iter, rand() % map.size());
        id_src = iter->first;
        iter = map.begin();
        advance(iter, rand() % map.size());
        id_dest = iter->first;
        auto start = high_resolution_clock::now();
        spAlgorithm(id_src, id_dest);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        total += duration.count();
        min_d = min(min_d, (long) duration.count());
        max_d = max(max_d, (long) duration.count());
    }

    double average = (double) total / (double) num_iter;

    cout << "Minimum run time: " << min_d << endl;
    cout << "Maximum run time: " << max_d << endl;
    cout << "Average run time: " << average << endl;
    cout << "Total run time: " << total << endl;

    enterWait();
}

void dijkstraPerfTest(Graph<coordinates> &graph) {
    shortestPathPerfTest(graph, [&](int s, int d) { return graph.dijkstraShortestPath(s, d); }, 'D');
}

void dijkstraBiDirPerfTest(Graph<coordinates> &graph) {
    shortestPathPerfTest(graph, [&](int s, int d) { return graph.dijkstraBiDirShortestPath(s, d); }, 'E');
}

void astarPerfTest(Graph<coordinates> &graph) {
    shortestPathPerfTest(graph, [&](int s, int d) { return graph.astarShortestPath(s, d); }, 'A');
}

void astarBiDirPerfTest(Graph<coordinates> &graph) {
    shortestPathPerfTest(graph, [&](int s, int d) { return graph.astarBiDirShortestPath(s, d); }, 'B');
}

void tarjanPerfTest(Graph<coordinates> &graph) {
    int num_iter;
    getOption(num_iter, "Number of iterations: ");

    long total = 0, min_d = LONG_MAX, max_d = 0;

    for (int i = 0; i < num_iter; i++) {
        auto start = high_resolution_clock::now();
        graph.tarjan(0);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        total += duration.count();
        min_d = min(min_d, (long) duration.count());
        max_d = max(max_d, (long) duration.count());
    }

    double average = (double) total / (double) num_iter;

    cout << "Minimum run time: " << min_d << endl;
    cout << "Maximum run time: " << max_d << endl;
    cout << "Average run time: " << average << endl;
    cout << "Total run time: " << total << endl;

    enterWait();
}

void tspPerfTest(Graph<coordinates> &graph, const function<Path (int id_src, int id_dest, vector<int> &POIs, vector<int> &ord, Path &path)> &tspAlgorithm) {
    int id_src, id_dest, num_iter, num_pois;
    getOption(num_iter, "Number of iterations: ", [&](int a){ return a > 0; });
    getOption(num_pois, "Number of POIs: ", [&](int a){ return a > 0 && a < graph.getVertexSet().size(); });

    long total = 0, min_d = LONG_MAX, max_d = 0;

    auto map = graph.getVertexMap();
    auto iter = map.begin();
    advance(iter, rand() % map.size());
    id_src = iter->first;
    iter = map.begin();
    advance(iter, rand() % map.size());
    id_dest = iter->first;

    vector<int> POIs_og;
    for (int i = 0; i < num_pois; i++) {
        auto iter = map.begin();
        advance(iter, rand() % map.size());
        POIs_og.push_back(iter->first);
    }

    for (int i = 0; i < num_iter; i++) {
        vector<int> POIs = POIs_og;
        vector<int> ord;
        Path path;
        auto start = high_resolution_clock::now();
        tspAlgorithm(id_src, id_dest, POIs, ord, path);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        total += duration.count();
        min_d = min(min_d, (long) duration.count());
        max_d = max(max_d, (long) duration.count());
    }

    double average = (double) total / (double) num_iter;

    cout << "Minimum run time: " << min_d << endl;
    cout << "Maximum run time: " << max_d << endl;
    cout << "Average run time: " << average << endl;
    cout << "Total run time: " << total << endl;

    enterWait();
}

void nnsPerfTest(Graph<coordinates> &graph) {
    tspPerfTest(graph, [&](int id_src, int id_dest, vector<int> &POIs, vector<int> &ord, Path &path){ return graph.nearestNeighborsSearch(id_src, id_dest, POIs, ord, path); });
}

void rnnsPerfTest(Graph<coordinates> &graph) {
    tspPerfTest(graph, [&](int id_src, int id_dest, vector<int> &POIs, vector<int> &ord, Path &path){ return graph.RNNeighborsSearch(id_src, id_dest, POIs, ord, path, 3); });
}

void twoptPerfTest(Graph<coordinates> &graph) {
    tspPerfTest(graph, [&](int id_src, int id_dest, vector<int> &POIs, vector<int> &ord, Path &path){ graph.nearestNeighborsSearch(id_src, id_dest, POIs, ord, path); return graph.twoOpt(ord, path); });
}
