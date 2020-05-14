#include "MapParser.h"

Graph<coordinates> parseGridMap(const string &nodes_file, const string &edges_file) {
    Graph<coordinates> graph;
    string line;

    ifstream nodes;
    nodes.open(nodes_file);

    getline(nodes, line);
    int num_nodes = stoi(line);

    for (int i = 0; i < num_nodes; i++) {
        getline(nodes, line);
        stringstream ss(line);
        string entry;
        int id, x, y;
        getline(ss, entry, '(');
        getline(ss, entry, ',');
        id = stoi(entry);
        getline(ss, entry, ',');
        x = stoi(entry);
        getline(ss, entry, ')');
        y = stoi(entry);
        graph.addVertex(id, make_pair(x, y));
    }

    nodes.close();

    ifstream edges;
    edges.open(edges_file);

    if (!edges.is_open()) { printf("POOOOP\n"); }

    getline(edges, line);
    int num_edges = stoi(line);

    for (int i = 0; i < num_edges; i++) {
        getline(edges, line);
        stringstream ss(line);
        string entry;
        int s, d;
        getline(ss, entry, '(');
        getline(ss, entry, ',');
        s = stoi(entry);
        getline(ss, entry, ')');
        d = stoi(entry);
        double cost = euclidianDistance(graph.findVertex(s)->getInfo(), graph.findVertex(d)->getInfo());
        graph.addEdge(s, d, cost);
        graph.addEdge(d, s, cost);
    }

    edges.close();

    return graph;
}