#include "UI.h"

UI::UI(Graph<coordinates> &graph, int width, int height) : graph(graph), gv_width(width), gv_height(height) {
    this->gv = new GraphViewer(width, height, false);
}

void UI::setGraph(Graph<coordinates> &graph) { this->graph = graph; }

void UI::showGraph() {
    gv->createWindow(gv_width, gv_height);
    double yPercent, xPercent;

    for (Vertex<coordinates>* vertex : graph.getVertexSet()) {
        yPercent = 1.0 - ((vertex->getInfo().second - graph.getMinY())/(graph.getMaxY() - graph.getMinY())*0.9 + 0.05);
        xPercent = (vertex->getInfo().first - graph.getMinX())/(graph.getMaxX() - graph.getMinX())*0.9 + 0.05;

        gv->addNode(vertex->getId(), (int)(xPercent*gv_width), (int)(yPercent*gv_height));
        gv->setVertexLabel(vertex->getId(), to_string(vertex->getId()));
    }

    int id = 0;
    for (Vertex<coordinates>* vertex : graph.getVertexSet()) {
        for (Edge<coordinates>* edge : vertex->getAdj()) {
            gv->addEdge(id, vertex->getId(), edge->getDest()->getId(), EdgeType::DIRECTED);
            gv->setEdgeLabel(id, to_string(edge->getCost()));
            id++;
        }
    }
}

void UI::showPath(vector<int> path) {
    gv->createWindow(gv_width, gv_height);
    for (int i = 0; i < path.size() - 1; i++) {
        Vertex<coordinates>* a = graph.findVertex(path.at(i));
        Vertex<coordinates>* b = graph.findVertex(path.at(i+1));
        gv->addNode(i, a->getInfo().first, a->getInfo().second);
        gv->setVertexLabel(i, to_string(a->getId()));
        gv->addNode(i+1, b->getInfo().first, b->getInfo().second);
        gv->setVertexLabel(i+1, to_string(b->getId()));
        gv->addEdge(i, i, i+1, EdgeType::DIRECTED);
        gv->setEdgeLabel(i, to_string(a->getCostTo(b->getId())));
    }
    gv->rearrange();
}
