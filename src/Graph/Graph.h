#ifndef PROJ_GRAPH_H
#define PROJ_GRAPH_H

#include <vector>

using namespace std;

typedef pair<double, double> coordinates;

template<class T> class Edge;
template<class T> class Graph;

//==============================
//  Vertex
//==============================
template<class T>
class Vertex {
    int id;
    T info;
    vector<Edge<T> *> outgoing;
    vector<Edge<T> *> incoming;

    Edge<T>* addEdge(Vertex<T> *dest, double cost);
    Vertex(T info);

    bool visited;
    Edge<T> *path;
public:
    int getId() const;
    T getInfo() const;
    vector<Edge<T> *> getAdj() const;
    friend class Graph<T>;
};

template<class T>
Vertex<T>::Vertex(T info): info(info) {}

template<class T>
Edge<T>* Vertex<T>::addEdge(Vertex<T> *dest, double cost) {
    Edge<T> *edge = new Edge<T>(this, dest, cost);
    this->outgoing.push_back(edge);
    dest->incoming.push_back(edge);
    return edge;
}

template<class T>
int Vertex<T>::getId() const { return id; }

template<class T>
T Vertex<T>::getInfo() const { return info; }

template<class T>
vector<Edge<T> *> Vertex<T>::getAdj() const { return outgoing; }

//==============================
//  Edge
//==============================
template<class T>
class Edge {
    Vertex<T> *orig;
    Vertex<T> *dest;
    double cost;

    Edge(Vertex<T> *orig, Vertex<T> *dest, double cost);
public:
    Vertex<T> *getOrig() const;
    Vertex<T> *getDest() const;
    double getCost() const;

    friend class Graph<T>;
    friend class Vertex<T>;
};

template<class T>
Edge<T>::Edge(Vertex<T> *orig, Vertex<T> *dest, double cost) : orig(orig), dest(dest), cost(cost) {}

template<class T>
Vertex<T> *Edge<T>::getOrig() const {
    return orig;
}

template<class T>
Vertex<T> *Edge<T>::getDest() const {
    return dest;
}

template<class T>
double Edge<T>::getCost() const {
    return cost;
}

//==============================
//  Graph
//==============================
template<class T>
class Graph {
    vector<Vertex<T> *> vertexSet;

    Vertex<T>* findVertex(const T &info) const;
    Vertex<T>* findVertex(const int &id) const;
public:
    vector<Vertex<T> *> getVertexSet() const;
    Vertex<T> *addVertex(const T &in);
    Edge<T> *addEdge(const T &sourc, const T &dest, double cost);
    Edge<T> *addEdge(const int id_src, const int id_dest, double cost);
};

template<class T>
Vertex<T>* Graph<T>::findVertex(const T &info) const {
    for (Vertex<T>* vertex : vertexSet) {
        if (vertex->info == info) {
            return vertex;
        }
    }
    return nullptr;
}

template<class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const { return vertexSet; }

template<class T>
Vertex<T>* Graph<T>::addVertex(const T &in) {
    Vertex<T> *v = findVertex(in);
    if (v != nullptr) {
        return v;
    }
    v = new Vertex<T>(in);
    v->id = vertexSet.size();
    vertexSet.push_back(v);
    return v;
}

template<class T>
Edge<T>* Graph<T>::addEdge(const T &sourc, const T &dest, double cost) {
    Vertex<T>* s = findVertex(sourc);
    Vertex<T>* d = findVertex(dest);
    if (s == nullptr || d == nullptr) { return nullptr; }
    else {
        return s->addEdge(d, cost);
    }
}

template<class T>
Edge<T> *Graph<T>::addEdge(const int id_src, const int id_dest, double cost) {
    Vertex<T>* s = findVertex(id_src);
    Vertex<T>* d = findVertex(id_dest);
    if (s == nullptr || d == nullptr) { return nullptr; }
    else {
        return s->addEdge(d, cost);
    }
}

template<class T>
Vertex<T> *Graph<T>::findVertex(const int &id) const {
    if (id < 0 || id >= vertexSet.size()) { return nullptr; }
    else { return vertexSet.at(id); }
}


#endif //PROJ_GRAPH_H
