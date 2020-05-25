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

    /*ofstream log;
    log.open(LOG_FILE, ofstream::app);

    log << test << "," << id_src << "," << id_dest << "," << min_d << "," << max_d << "," << average << "," << total
        << "," << num_iter << "," << endl;

    log.close();*/

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

void clearLog() {
    ofstream log;
    log.open(LOG_FILE, ofstream::trunc);
    log.close();
}
