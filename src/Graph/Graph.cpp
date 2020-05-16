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
coordinates Graph<T>::getMinCoords() const {
    return minCoords;
}

template<class T>
coordinates Graph<T>::getMaxCoords() const {
    return maxCoords;
}


template<class T>
Vertex<T> * Graph<T>::addVertex(int id, const T &in) {
    if (vertexMap.count(id) != 0) {
        return nullptr;
    }
    Vertex<T> *v = new Vertex<T>(in);
    if (vertexSet.empty()) {
        this->minCoords = make_pair(v->getInfo().first, v->getInfo().second);
        this->maxCoords = make_pair(v->getInfo().first, v->getInfo().second);
    }
    else {
        if(v->getInfo().first > maxCoords.first)
            maxCoords.first = v->getInfo().first;
        else if(v->getInfo().first < minCoords.first)
            minCoords.first = v->getInfo().first;
        if(v->getInfo().second > maxCoords.second)
            maxCoords.second = v->getInfo().second;
        else if (v->getInfo().second < minCoords.second)
            minCoords.second = v->getInfo().second;
    }
    v->id = id;
    vertexSet.push_back(v);
    vertexMap.insert(make_pair(id, vertexSet.size() - 1));
    return v;
}

template<class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const { return vertexSet; }

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
    auto i = vertexMap.find(id);
    if (i == vertexMap.end()) {
        return nullptr;
    }
    return vertexSet.at(i->second);
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

/******Shortest Path******/
template<class T>
Path Graph<T>::genericShortestPath(const int id_src, const int id_dest, function<double (T, T)> h) {
    for (Vertex<T> *vert: vertexSet) {
        vert->dist = INT_MAX;
        vert->path = NULL;
        vert->queueIndex = 0;
    }

    Vertex<T> *src = findVertex(id_src), *dest = findVertex(id_dest), *v;
    src->dist = h(src->getInfo(), dest->getInfo());
    MutablePriorityQueue<Vertex<T>> Q;
    Q.insert(src);

    while (!Q.empty()){
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

    vector<int> path;
    double length = 0;
    path.push_back(dest->id);
    Vertex<T>* vertex = dest;

    while (vertex->path != NULL) {
        length += vertex->path->getCostTo(vertex->id);
        vertex = vertex->path;
        path.emplace(path.begin(), vertex->id);
    }

    return Path(length, path);
}

/******Dijkstra******/

template<class T>
Path Graph<T>::dijkstraShortestPath(const int id_src, const int id_dest) {
    return genericShortestPath(id_src, id_dest, [&](T a, T b){ return 0; });
}

/******A-Star******/

template<class T>
Path Graph<T>::astarShortestPath(const int id_src, const int id_dest) {
    return genericShortestPath(id_src, id_dest, euclidianDistance);
}

/******NNS******/

template<class T>
Path Graph<T>::find_nearest(const int &id_src, const vector<int> &POIs){
    Path path = Path(INT_MAX, vector<int>());

    for (int i : POIs) {
        Path i_path = astarShortestPath(id_src, i);

        if (i_path.getLength() < path.getLength()) {
            path = i_path;
        }
    }

    return path;
}

template<class T>
vector<Path> Graph<T>::find_n_nearest(const int &id_src, const vector<int> &POIs, const int &n) {
    vector<Path> dists;
    for (int point : POIs) {
        dists.push_back(astarShortestPath(id_src, point));
    }

    if (dists.size() <= n) { return dists; }

    sort(dists.begin(), dists.end(), [&](Path &i, Path &j){ return i.getLength() < j.getLength(); });

    return vector<Path>(dists.begin(), dists.begin() + n);
}

template<class T>
vector<int> Graph<T>::nearestNeighborsSearch(const int &id_src, const int &id_dest, vector<int> &POIs, vector<int> &ord, Path &path){
    ord.push_back(id_src);
    if (ord.size() == 1) {
        path.addNode(id_src);
    }

    if (POIs.empty()) {
        ord.push_back(id_dest);
        Path last = astarShortestPath(path.getLastNode(), id_dest);
        path.joinPath(last);
        return ord;
    }

    Path next = find_nearest(id_src, POIs);
    path.joinPath(next);
    POIs.erase(find(POIs.begin(), POIs.end(), path.getLastNode()));

    return nearestNeighborsSearch(path.getLastNode(), id_dest, POIs, ord, path);
}

template<class T>
vector<int> Graph<T>::RNNeighborsSearch(const int &id_src, const int &id_dest, vector<int> &POIs, vector<int> &ord, Path &path, const int &n) {
    ord.push_back(id_src);
    if (ord.size() == 1) {
        path.addNode(id_src);
    }

    if (POIs.empty()) {
        ord.push_back(id_dest);
        Path last = astarShortestPath(path.getLastNode(), id_dest);
        path.joinPath(last);
        return ord;
    }

    vector<Path> neighbors = find_n_nearest(id_src, POIs, n);
    int next_i = rand() % neighbors.size();
    Path next = neighbors.at(next_i);
    path.joinPath(next);
    POIs.erase(find(POIs.begin(), POIs.end(), path.getLastNode()));

    return RNNeighborsSearch(path.getLastNode(), id_dest, POIs, ord, path, n);
}

template<class T>
Path Graph<T>::buildPath(const vector<int> &ord) {
    Path path;
    for (int i = 0; i < ord.size() - 1; i++) {
        path.joinPath(astarShortestPath(ord[i], ord[i+1]));
    }
    return path;
}

template<class T>
Path Graph<T>::twoOpt(const vector<int> &ord, const Path &path) {
    int improve = 0;
    Path best = path;

    while (improve < 20) {
        for (int i = 1; i < ord.size() - 2; i++) {
            for (int k = i + 1; k < ord.size() - 1; k++) {
                Path new_path = buildPath(twoOptSwap(ord, i, k));
                if (new_path.getLength() < best.getLength()) {
                    improve = 0;
                    best = new_path;
                }
            }
        }
        improve++;
    }

    return best;
}

template<class T>
vector<int> Graph<T>::twoOptSwap(const vector<int> &ord, const int &i, const int &k) {
    vector<int> new_ord;

    for (int c = 0; c < i; c++) {
        new_ord.push_back(ord.at(c));
    }

    for (int c = k; c >= i; c--) {
        new_ord.push_back(ord.at(c));
    }

    for (int c = k + 1; c < ord.size(); c++) {
        new_ord.push_back(ord.at(c));
    }

    return new_ord;
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
