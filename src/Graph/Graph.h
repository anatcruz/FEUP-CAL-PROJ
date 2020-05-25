#ifndef PROJ_GRAPH_H
#define PROJ_GRAPH_H

#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <climits>
#include <functional>
#include <algorithm>
#include <thread>
#include <unordered_map>
#include "MutablePriorityQueue.h"
#include "Path.h"
#include "Route.h"
#include "Utils/Utils.h"

using namespace std;

template<class T> class Edge;
template<class T> class Graph;

enum Tag {quinta, garagem, cliente, none};

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

    // DFS
    bool visited;

    // Pathfinding
    Vertex<T>* path = NULL;
    double dist = 0;
    Vertex<T>* path_inv = NULL;
    double dist_inv = 0;

    // Tarjan
    int index = -1;
    int low = -1;
    bool onStack = false;
public:
    int queueIndex = 0; // For MPQ
    int queueIndexInv = 0; // For MPQ

    Tag tag = none;

    int getId() const;
    T getInfo() const;
    double getDist() const;
    vector<Edge<T> *> getAdj() const;
    double getCostTo(int dest_id) const;

    bool compare(const Vertex &rhs, bool inv);

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
    unordered_map<int, int> vertexMap;

    coordinates minCoords, maxCoords;

    void dfsVisit(Vertex<T>* v, vector<int> &res) const;
public:
    bool isGrid;

    coordinates getMinCoords() const;
    coordinates getMaxCoords() const;

    vector<Vertex<T> *> getVertexSet() const;

    unordered_map<int, int> getVertexMap() const;

    Vertex<T> *addVertex(int id, const T &in);
    Edge<T> *addEdge(const int id_src, const int id_dest, double cost);

    void clearGraph();
    void makePathGraph(const vector<int> &path);

    Vertex<T>* findVertex(const int &id) const;
    bool isValidID(const int &id);
    void getValidID(int &id, const string &message);

    vector<int> dfs() const;
    vector<int> dfs(const int id_src) const;

    Path genericShortestPath(const int id_src, const int id_dest, function<double(T, T)> h);
    Path genericBiDirShortestPath(const int id_src, const int id_dest, function<double(T, T)> h);
    Path dijkstraShortestPath(const int id_src, const int id_dest);
    Path dijkstraBiDirShortestPath(const int id_src, const int id_dest);
    Path astarShortestPath(const int id_src, const int id_dest);
    Path astarBiDirShortestPath(const int id_src, const int id_dest);

    Path find_nearest(const int &id_src, const vector<int> &POIs);
    vector<Path> find_n_nearest(const int &id_src, const vector<int> &POIs, const int &n);
    Path nearestNeighborsSearch(const int &id_src, const int &id_dest, vector<int> &POIs, vector<int> &ord, Path &path);
    Path RNNeighborsSearch(const int &id_src, const int &id_dest, vector<int> &POIs, vector<int> &ord, Path &path, const int &n);
    Path buildPath(const vector<int> &ord);
    Path twoOpt(vector<int> &ord, const Path &path);
    vector<int> twoOptSwap(const vector<int> &ord, const int &i, const int &k);

    vector<vector<int>> tarjan(const int id_src);
    void strongconnect(Vertex<T>* src, int &index, stack<Vertex<T>*> &st, vector<vector<int>> &scc);

    vector<Route> sweep(const int &centre_id, vector<double> &capacities, vector<deliverypoint> &POIs);
    double angleBetweenNodes(const int &a, const int &b, const int &offset = -1);
};

#endif //PROJ_GRAPH_H
