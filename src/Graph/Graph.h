#ifndef PROJ_GRAPH_H
#define PROJ_GRAPH_H

#include <vector>
#include <climits>
#include "MutablePriorityQueue.h"

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
    Vertex<T>* path = NULL;
    double dist = 0;
public:
    int queueIndex = 0; // For MPQ

    int getId() const;
    T getInfo() const;
    double getDist() const;
    vector<Edge<T> *> getAdj() const;

    bool operator<(const Vertex &rhs) const;

    bool operator>(const Vertex &rhs) const;

    bool operator<=(const Vertex &rhs) const;

    bool operator>=(const Vertex &rhs) const;

    friend class Graph<T>;
};


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


//==============================
//  Graph
//==============================
template<class T>
class Graph {
    vector<Vertex<T> *> vertexSet;

    Vertex<T>* findVertex(const T &info) const;
    Vertex<T>* findVertex(const int &id) const;

    void dfsVisit(Vertex<T>* v, vector<int> &res) const;
public:
    vector<Vertex<T> *> getVertexSet() const;
    Vertex<T> *addVertex(const T &in);
    Edge<T> *addEdge(const T &sourc, const T &dest, double cost);
    Edge<T> *addEdge(const int id_src, const int id_dest, double cost);

    vector<int> dfs() const;
    vector<int> dfs(const int id_src) const;

    vector<int> dijkstraShortestPath(const int id_src, const int id_dest);
};

#endif //PROJ_GRAPH_H
