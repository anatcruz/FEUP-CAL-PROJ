#include "PerformanceTesting.h"

void dijkstraPerfTest(Graph<coordinates> &graph) {
    int id_src, id_dest, num_iter;
    getOption(id_src, "Source node ID: ");
    getOption(id_dest, "Destination node ID: ");
    getOption(num_iter, "Number of iterations: ");

    long total = 0, min_d = LONG_MAX, max_d = 0;

    for (int i = 0; i < num_iter; i++) {
        auto start = high_resolution_clock::now();
        Path path = graph.dijkstraShortestPath(id_src, id_dest);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        total += duration.count();
        min_d = min(min_d, duration.count());
        max_d = max(max_d, duration.count());
    }

    double average = (double) total / (double) num_iter;

    cout << "Minimum run time: " << min_d << endl;
    cout << "Maximum run time: " << max_d << endl;
    cout << "Average run time: " << average << endl;
    cout << "Total run time: " << total << endl;

    enterWait();
}

void astarPerfTest(Graph<coordinates> &graph) {
    int id_src, id_dest, num_iter;
    getOption(id_src, "Source node ID: ");
    getOption(id_dest, "Destination node ID: ");
    getOption(num_iter, "Number of iterations: ");

    long total = 0, min_d = LONG_MAX, max_d = 0;

    for (int i = 0; i < num_iter; i++) {
        auto start = high_resolution_clock::now();
        Path path = graph.astarShortestPath(id_src, id_dest);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        total += duration.count();
        min_d = min(min_d, duration.count());
        max_d = max(max_d, duration.count());
    }

    double average = (double) total / (double) num_iter;

    cout << "Minimum run time: " << min_d << endl;
    cout << "Maximum run time: " << max_d << endl;
    cout << "Average run time: " << average << endl;
    cout << "Total run time: " << total << endl;

    enterWait();
}