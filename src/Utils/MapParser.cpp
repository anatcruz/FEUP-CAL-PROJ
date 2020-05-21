#include "MapParser.h"

Graph<coordinates> parseMap(const string &nodes_file, const string &edges_file, bool grid) {
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


Farm loadContext(Graph<coordinates> &graph, const string &farm_file, const string &clients_file) {
    string line;
    ifstream tags;

    //Read farm file
    tags.open(farm_file);

    getline(tags, line);
    int farmNodeID = stoi(line);
    auto vertex = graph.findVertex(farmNodeID);
    vertex->tag = quinta;
    Farm farm = Farm(farmNodeID);

    getline(tags, line);
    int garageNodeID = stoi(line);
    vertex = graph.findVertex(garageNodeID);
    vertex->tag = garagem;
    Garage garage = Garage(garageNodeID);

    getline(tags, line);
    int num_trucks = stoi(line);
    for(int i=0; i<num_trucks; i++){
        getline(tags, line);
        string plate = line;
        getline(tags, line);
        int capacity = stoi(line);
        garage.addTruck(Truck(capacity, plate));
    }
    farm.setGarage(garage);

    tags.close();

    tags.open(clients_file);
    while(getline(tags, line)){
        int nif = stoi(line);
        getline(tags, line);
        int id = stoi(line);
        farm.addClient(Client(id,nif));
        vertex = graph.findVertex(id);
        vertex->tag = cliente;

        getline(tags,line);
        int num_baskets = stoi(line);
        for (int i=0; i<num_baskets; i++){
            getline(tags,line);
            farm.addBasket(Basket(stoi(line), nif));
        }
    }

    return farm;
}
