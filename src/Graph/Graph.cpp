#include <iostream>
#include "Graph.h"

//==============================
//  Vertex
//==============================
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

template<class T>
double Vertex<T>::getDist() const { return dist; }

template<class T>
bool Vertex<T>::operator<(const Vertex &rhs) const {
    return this->dist < rhs.dist;
}

template<class T>
bool Vertex<T>::operator>(const Vertex &rhs) const {
    return rhs < *this;
}

template<class T>
bool Vertex<T>::operator<=(const Vertex &rhs) const {
    return !(rhs < *this);
}

template<class T>
bool Vertex<T>::operator>=(const Vertex &rhs) const {
    return !(*this < rhs);
}


//==============================
//  Edge
//==============================
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
Vertex<T> * Graph<T>::addVertex(const T &in) {
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

//==============================
//  Algorithms
//==============================

/******DFS******/

template<class T>
vector<int> Graph<T>::dfs() const {
    vector<int> result;
    for (auto vertex : vertexSet) {
        vertex->visited = false;
    }
    for (auto vertex : vertexSet) {
        if (!vertex->visited) { dfsVisit(vertex, result); }
    }
    return result;
}

template<class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<int> &res) const {
    v->visited = true;
    res.push_back(v->getId());
    for (auto edge : v->getAdj()) {
        if (!edge->dest->visited) { dfsVisit(edge->dest, res); }
    }
}

template<class T>
vector<int> Graph<T>::dfs(const int id_src) const {
    vector<int> result;
    for (auto vertex : vertexSet) {
        vertex->visited = false;
    }
    dfsVisit(this->findVertex(id_src), result);
    return result;
}

/******Dijkstra******/

template<class T>
void Graph<T>::dijkstraShortestPath(const int id_src, const int id_dest) {
    for (Vertex<T> *vert: vertexSet) {
        vert->dist = INT_MAX;
        vert->path = NULL;
    }

    Vertex<T> *src = findVertex(id_src), *dest = findVertex(id_dest), *v;
    src->dist=0;
    MutablePriorityQueue<Vertex<T>> Q;
    Q.insert(src);

    while (!Q.empty()){
        v = Q.extractMin();
        std::cout << v->getId();

        if (v == dest){
            break;
        }

        for (Edge<T> *w: v->outgoing){
            if (w->dest->getDist() > v->dist +  w->getCost()){
                double d = w->dest->getDist();
                w->dest->dist = v->dist +  w->getCost();
                w->dest = v;
                if (d == INT_MAX){
                    Q.insert(w->dest);
                }
                else {
                    Q.decreaseKey(w->dest);
                }
            }
        }
    }
}

template class Vertex<coordinates>;
template class Edge<coordinates>;
template class Graph<coordinates>;
