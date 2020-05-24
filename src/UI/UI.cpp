#include "UI.h"

UI::UI(Graph<coordinates> *graph, int width, int height) : graph(graph), gv_width(width), gv_height(height) {}

void UI::setGraph(Graph<coordinates> *graph) { this->graph = graph; }

void UI::showGraph() {
    this->gv = new GraphViewer(gv_width, gv_height, false);
    gv->defineEdgeCurved(false);
    gv->createWindow(gv_width, gv_height);

    for (Vertex<coordinates>* vertex : graph->getVertexSet()) {
        gv->addNode(vertex->getId(), x_fitted(vertex->getInfo().first), y_fitted(vertex->getInfo().second));
        setNodeProperties(vertex, vertex->getId());

        if (graph->isGrid)
            gv->setVertexLabel(vertex->getId(), to_string(vertex->getId()));
    }

    int id = 0;
    for (Vertex<coordinates>* vertex : graph->getVertexSet()) {
        for (Edge<coordinates>* edge : vertex->getAdj()) {
            gv->addEdge(id, vertex->getId(), edge->getDest()->getId(), EdgeType::UNDIRECTED);
            id++;
        }
    }

    enterWait();
    delete gv;
}

void UI::showPath(vector<int> path) {
    this->gv = new GraphViewer(gv_width, gv_height, false);
    gv->defineEdgeCurved(false);
    gv->createWindow(gv_width, gv_height);

    Vertex<coordinates>* a = graph->findVertex(path.at(0));
    gv->addNode(0, x_fitted(a->getInfo().first), y_fitted(a->getInfo().second));
    setNodeProperties(a, 0);

    for (int i = 1; i < path.size(); i++) {
        a = graph->findVertex(path.at(i));

        gv->addNode(i, x_fitted(a->getInfo().first), y_fitted(a->getInfo().second));
        gv->addEdge(i, i-1, i, EdgeType::DIRECTED);
        setNodeProperties(a, i);
    }
    gv->rearrange();

    enterWait();
    delete gv;
}

void UI::showDeliveryPath(vector<int> path, vector<int> POIs) {
    this->gv = new GraphViewer(gv_width, gv_height, false);
    gv->defineEdgeCurved(false);
    gv->defineVertexSize(3);
    gv->createWindow(gv_width, gv_height);
    int current_POI = -1;

    if (!POIs.empty()) {
        current_POI = 0;
    }

    Vertex<coordinates> *a = graph->findVertex(path.at(0));
    gv->addNode(0, x_fitted(a->getInfo().first), y_fitted(a->getInfo().second));
    if (current_POI != -1 && a->getId() == POIs.at(current_POI)) {
        setPOIProperties(a, 0, current_POI);
        if (++current_POI >= POIs.size()) { current_POI = -1; }
    }

    for (int i = 1; i < path.size(); i++) {
        a = graph->findVertex(path.at(i));

        gv->addNode(i, x_fitted(a->getInfo().first), y_fitted(a->getInfo().second));
        if (current_POI != -1 && a->getId() == POIs.at(current_POI)) {
            setPOIProperties(a, i, current_POI);
            if (++current_POI >= POIs.size()) { current_POI = -1; }
        }
        gv->addEdge(i, i-1, i, EdgeType::DIRECTED);
    }

    gv->rearrange();

    enterWait();
    delete gv;
}

void UI::showRoutes(vector<vector<int>> routes, vector<vector<int>> POIs) {
    if (routes.empty()) { return; }

    this->gv = new GraphViewer(gv_width, gv_height, false);
    gv->defineEdgeCurved(false);
    gv->defineVertexSize(3);
    gv->createWindow(gv_width, gv_height);
    int current_POI = -1;
    int current_route = 0;
    int node_id = 0;

    if (!POIs.at(current_route).empty()) {
        current_POI = 0;
    }

    Vertex<coordinates> *a = graph->findVertex(routes.at(0).at(0)); // Gets first node, same for all routes
    gv->addNode(node_id, x_fitted(a->getInfo().first), y_fitted(a->getInfo().second));
    if (current_POI != -1 && a->getId() == POIs.at(current_route).at(current_POI)) {
        setPOIProperties(a, node_id, current_POI);
        if (++current_POI >= POIs.at(current_route).size()) { current_POI = -1; }
    }
    node_id++;

    for (current_route; current_route < routes.size(); current_route++) {
        if (current_route > 0) {
            if (POIs.at(current_route).size() >= 2) { current_POI = 1; }
            else { current_POI = -1; }
        }
        for (int i = 1; i < routes.at(current_route).size(); i++) {
            a = graph->findVertex(routes.at(current_route).at(i));

            gv->addNode(node_id, x_fitted(a->getInfo().first), y_fitted(a->getInfo().second));
            if (current_POI != -1 && a->getId() == POIs.at(current_route).at(current_POI)) {
                setPOIProperties(a, node_id, current_POI);
                if (++current_POI >= POIs.at(current_route).size()) { current_POI = -1; }
            }
            if (i == 1) {
                gv->addEdge(node_id, 0, node_id, EdgeType::DIRECTED);
            } else {
                gv->addEdge(node_id, node_id - 1, node_id, EdgeType::DIRECTED);
            }
            gv->setEdgeLabel(node_id, to_string(current_route));
            node_id++;
        }
    }

    gv->rearrange();

    enterWait();
    delete gv;
}

int UI::x_fitted(double x) {
    return (x - graph->getMinCoords().first) * (gv_width - 50) / (graph->getMaxCoords().first - graph->getMinCoords().first) + 25;
}

int UI::y_fitted(double y) {
    return (y - graph->getMinCoords().second) * (gv_height - 50) / (graph->getMaxCoords().second - graph->getMinCoords().second) + 25;
}

void UI::setNodeProperties(Vertex<coordinates> *node, int id) {
    switch (node->tag) {
        case quinta:
            gv->setVertexSize(id, 10);
            gv->setVertexColor(id, "BLUE");
            break;
        case garagem:
            gv->setVertexSize(id, 10);
            gv->setVertexColor(id, "ORANGE");
            break;
        case cliente:
            gv->setVertexSize(id, 10);
            gv->setVertexColor(id, "RED");
            break;
        case none:
            gv->setVertexSize(id, 3);
            gv->setVertexColor(id, "YELLOW");
            break;
    }
}

void UI::setPOIProperties(Vertex<coordinates> *node, int id, int poi_n) {
    switch (node->tag) {
        case none:
            gv->setVertexSize(id, 10);
            gv->setVertexColor(id, "GREEN");
            break;
        default:
            setNodeProperties(node, id);
            break;
    }
    gv->setVertexLabel(id, to_string(poi_n));
}
