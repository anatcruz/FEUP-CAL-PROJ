#include "UI.h"

UI::UI(Graph<coordinates> &graph, int width, int height) : graph(graph), gv_width(width), gv_height(height) {
    this->gv = new GraphViewer(width, height, false);
}

void UI::setGraph(Graph<coordinates> &graph) { this->graph = graph; }

void UI::showGraph() {
    gv->createWindow(gv_width, gv_height);
    int id = 0;
    for (Vertex<coordinates>* vertex : graph.getVertexSet()) {
        gv->addNode(id, vertex->getInfo().first, vertex->getInfo().second);
        gv->setVertexLabel(id, to_string(vertex->getId()));
        id++;
    }
    id = 0;
    for (Vertex<coordinates>* vertex : graph.getVertexSet()) {
        for (Edge<coordinates>* edge : vertex->getAdj()) {
            gv->addEdge(id, vertex->getId(), edge->getDest()->getId(), EdgeType::DIRECTED);
            gv->setEdgeLabel(id, to_string(edge->getCost()));
            id++;
        }
    }
}
