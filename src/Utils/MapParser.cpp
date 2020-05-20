#include "MapParser.h"

Graph<coordinates> parseGridMap(const string &nodes_file, const string &edges_file, bool grid) {
    Graph<coordinates> graph;
    graph.isGrid = grid;
    string line;

    ifstream nodes;
    nodes.open(nodes_file);

    getline(nodes, line);
    int num_nodes = stoi(line);

    for (int i = 0; i < num_nodes; i++) {
        getline(nodes, line);
        stringstream ss(line);
        string entry;
        int id;
        double x, y;
        getline(ss, entry, '(');
        getline(ss, entry, ',');
        id = stoi(entry);
        getline(ss, entry, ',');
        x = stod(entry);
        getline(ss, entry, ')');
        y = stod(entry);
        graph.addVertex(id, make_pair(x, y));
    }

    nodes.close();

    ifstream edges;
    edges.open(edges_file);

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
        if (grid)
            graph.addEdge(d, s, cost);
    }

    edges.close();

    return graph;
}

void loadContext(Graph<coordinates> &graph, const string &tags_file) {
    string line;
    ifstream tags;
    tags.open(tags_file);

    while (getline(tags, line)) {
        stringstream ss(line);
        Tag tag = none;
        if (line == "Q") {
            tag = quinta;
        } else if (line == "G") {
            tag = garagem;
        } else if (line[0] == 'C') {
            tag = cliente;
        }
        getline(tags, line);
        int num_nodes = stoi(line);
        for (int i = 0; i < num_nodes; i++) {
            getline(tags, line);
            auto vertex = graph.findVertex(stoi(line));
            vertex->tag = tag;
        }
    }
}
