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
double Vertex<T>::getCostTo(int dest_id) const {
    for (auto e : outgoing) {
        if (e->dest->getId() == dest_id) {
            return e->getCost();
        }
    }
    return -1;
}

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
vector<int> Graph<T>::dijkstraShortestPath(const int id_src, const int id_dest) {
    for (Vertex<T> *vert: vertexSet) {
        vert->dist = INT_MAX;
        vert->path = NULL;
    }

    Vertex<T> *src = findVertex(id_src), *dest = findVertex(id_dest), *v;
    src->dist=0;
    MutablePriorityQueue<Vertex<T>> Q;
    Q.insert(src);

    int iter = 0;

    while (!Q.empty()){
        iter++;
        v = Q.extractMin();

        if (v == dest){
            break;
        }

        for (Edge<T> *w : v->getAdj()){
            if (w->dest->getDist() > v->dist +  w->getCost()){
                double d = w->dest->getDist();
                w->dest->dist = v->dist +  w->getCost();
                w->dest->path = v;
                if (d == INT_MAX){
                    Q.insert(w->dest);
                }
                else {
                    Q.decreaseKey(w->dest);
                }
            }
        }
    }

    cout << iter << endl;

    vector<int> path;
    path.push_back(dest->id);
    Vertex<T>* vertex = dest;

    while (vertex->path != NULL) {
        vertex = vertex->path;
        path.emplace(path.begin(), vertex->id);
    }

    cout << "Size: " << path.size() << endl;

    return path;
}

/******A-Star******/

template<class T>
vector<int> Graph<T>::astarShortestPath(const int id_src, const int id_dest, function<double (pair<double, double>, pair<double, double>)> h) {
    for (Vertex<T> *vert: vertexSet) {
        vert->dist = INT_MAX;
        vert->path = NULL;
    }

    Vertex<T> *src = findVertex(id_src), *dest = findVertex(id_dest), *v;
    src->dist = h(src->getInfo(), dest->getInfo());
    MutablePriorityQueue<Vertex<T>> Q;
    Q.insert(src);

    int iter = 0;

    while (!Q.empty()){
        iter++;
        v = Q.extractMin();

        if (v == dest){
            break;
        }

        for (Edge<T> *w : v->getAdj()){
            double f = v->dist - h(v->getInfo(), dest->getInfo()) +  w->getCost() + h(w->dest->getInfo(), dest->getInfo());
            if (w->dest->getDist() > f){
                double d = w->dest->getDist();
                w->dest->dist = f;
                w->dest->path = v;
                if (d == INT_MAX){
                    Q.insert(w->dest);
                }
                else {
                    Q.decreaseKey(w->dest);
                }
            }
        }
    }

    cout << iter << endl;

    vector<int> path;
    path.push_back(dest->id);
    Vertex<T>* vertex = dest;

    while (vertex->path != NULL) {
        vertex = vertex->path;
        path.emplace(path.begin(), vertex->id);
    }

    cout << "Size: " << path.size() << endl;

    return path;
}

/******NNS******/

template<class T>
int Graph<T>::find_nearest(const int &id_src, const vector<int> &POIs){
    int min = INT_MAX;
    double dist = INT_MAX;

    for (int i : POIs) {
        double i_dist = 0;
        vector<int> path = astarShortestPath(id_src, i, euclidianDistance);
        // TODO melhorar return da função path
        for (int j = 0; j < path.size() - 1; j++){
            Vertex<T> *v = findVertex(path.at(j));
            i_dist += v->getCostTo(path.at(j + 1));
        }

        if(i_dist < dist){
            min = i;
            dist = i_dist;
        }
    }

    return min;
}

template<class T>
vector<int> Graph<T>::find_n_nearest(const int &id_src, const vector<int> &POIs, const int &n) {
    vector<pair<int, double>> nearest;
    pair<int, double> max = make_pair(-1, -1);

    if (POIs.size() <= n) { return POIs; }

    for (int point : POIs) {
        double i_dist = 0;
        vector<int> path = astarShortestPath(id_src, point, euclidianDistance);
        for (int j = 0; j < path.size() - 1; j++) {
            Vertex<T> *v = findVertex(path.at(j));
            i_dist += v->getCostTo(path.at(j + 1));
        }

        if (nearest.size() < n) {
            nearest.push_back(make_pair(point, i_dist));
            if (max.first == -1) { max = nearest.back(); }
            else {
                for (auto item : nearest) {
                    if (item.second > max.second) {
                        max = item;
                    }
                }
            }
        } else if (i_dist < max.second) {
            auto it = find_if(nearest.begin(), nearest.end(), [&](pair<int, double> p) { return p.first == max.first; });
            *it = make_pair(point, i_dist);
            for (auto item : nearest) {
                if (item.second > max.second) {
                    max = item;
                }
            }
        }
    }

    vector<int> result;
    for (auto & it : nearest) {
        result.push_back(it.first);
    }
    return result;
}

template<class T>
vector<int> Graph<T>::nearestNeighborsSearch(const int &id_src, const int &id_dest, vector<int> &POIs, vector<int> &ord){
    ord.push_back(id_src);

    if (POIs.empty()) {
        ord.push_back(id_dest);
        return ord;
    }

    int next = find_nearest(id_src, POIs);
    POIs.erase(find(POIs.begin(), POIs.end(), next));

    return nearestNeighborsSearch(next, id_dest, POIs, ord);
}

/******Tarjan******/
// TODO mudar vector para hashtable
template<class T>
vector<vector<int>> Graph<T>::tarjan(const int id_src) {
    vector<vector<int>> scc;

    int index = 0;
    stack<Vertex<T>*> st;

    for (Vertex<T>* vertex : vertexSet) {
        if (vertex->index == -1) {
            strongconnect(vertex, index, st, scc);
        }
    }

    return scc;
}

template<class T>
void Graph<T>::strongconnect(Vertex<T>* src, int &index, stack<Vertex<T>*> &st, vector<vector<int>> &scc) {
    src->index = index;
    src->low = index;
    index++;
    st.push(src);
    src->onStack = true;

    for (Edge<T>* edge : src->getAdj()) {
        if (edge->dest->index == -1) {
            strongconnect(edge->dest, index, st, scc);
            src->low = min(src->low, edge->dest->low);
        } else if (edge->dest->onStack) {
            src->low = min(src->low, edge->dest->index);
        }
    }

    if (src->low == src->index) {
        vector<int> sc;
        Vertex<T>* w;
        do {
            w = st.top();
            st.pop();
            w->onStack = false;
            sc.push_back(w->getId());
        } while (w != src);
        scc.push_back(sc);
    }
}

template class Vertex<coordinates>;
template class Edge<coordinates>;
template class Graph<coordinates>;
