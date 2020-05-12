#ifndef PROJ_GRAPH_H
#define PROJ_GRAPH_H

#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <climits>
#include <functional>
#include <algorithm>
#include "MutablePriorityQueue.h"
#include "Utils/Utils.h"

using namespace std;

typedef pair<double, double> coordinates;
typedef pair<double, vector<int>> path_t;

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

    // Pathfinding
    bool visited;
    Vertex<T>* path = NULL;
    double dist = 0;

    // Tarjan
    int index = -1;
    int low = -1;
    bool onStack = false;
public:
    int queueIndex = 0; // For MPQ

    int getId() const;
    T getInfo() const;
    double getDist() const;
    vector<Edge<T> *> getAdj() const;
    double getCostTo(int dest_id) const;

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

    void dfsVisit(Vertex<T>* v, vector<int> &res) const;
public:
    vector<Vertex<T> *> getVertexSet() const;
    Vertex<T> *addVertex(const T &in);
    Edge<T> *addEdge(const T &sourc, const T &dest, double cost);
    Edge<T> *addEdge(const int id_src, const int id_dest, double cost);

    Vertex<T>* findVertex(const int &id) const;

    vector<int> dfs() const;
    vector<int> dfs(const int id_src) const;

    path_t genericShortestPath(const int id_src, const int id_dest, function<double(T, T)> h);
    path_t dijkstraShortestPath(const int id_src, const int id_dest);
    path_t astarShortestPath(const int id_src, const int id_dest);

    int find_nearest(const int &id_src, const vector<int> &POIs);
    vector<int> find_n_nearest(const int &id_src, const vector<int> &POIs, const int &n);
    vector<int> nearestNeighborsSearch(const int &id_src, const int &id_dest, vector<int> &POIs, vector<int> &ord);
    vector<int> RNNeighborsSearch(const int &id_src, const int &id_dest, vector<int> &POIs, vector<int> &ord, const int &n);

    vector<vector<int>> tarjan(const int id_src);
    void strongconnect(Vertex<T>* src, int &index, stack<Vertex<T>*> &st, vector<vector<int>> &scc);
};

#endif //PROJ_GRAPH_H
