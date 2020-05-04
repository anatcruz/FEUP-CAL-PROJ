#include "UI.h"

UI::UI(Graph<int> &graph, int width, int height) : graph(graph), gv_width(width), gv_height(height) {
    this->gv = new GraphViewer(width, height, false);
}

void UI::setGraph(Graph<int> &graph) { this->graph = graph; }

void UI::showGraph() {
    gv->createWindow(gv_width, gv_height);
    int id = 0;
    for (Vertex<int>* vertex : graph.getVertexSet()) {
        gv->addNode(id, (id + 1) * 100, (id + 1) * 100);
        gv->setVertexLabel(id, to_string(vertex->getInfo()));
        id++;
    }
    id = 0;
    for (Vertex<int>* vertex : graph.getVertexSet()) {
        for (Edge<int>* edge : vertex->getAdj()) {
            gv->addEdge(id, vertex->getId(), edge->getDest()->getId(), EdgeType::DIRECTED);
            gv->setEdgeLabel(id, to_string(edge->getCost()));
            id++;
        }
    }
}
