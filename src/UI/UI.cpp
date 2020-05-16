#include "UI.h"

UI::UI(Graph<coordinates> *graph, int width, int height) : graph(graph), gv_width(width), gv_height(height) {}

void UI::setGraph(Graph<coordinates> *graph) { this->graph = graph; }

void UI::showGraph() {
    this->gv = new GraphViewer(gv_width, gv_height, false);
    gv->defineEdgeCurved(false);
    gv->createWindow(gv_width, gv_height);
    double yPercent, xPercent;

    for (Vertex<coordinates>* vertex : graph->getVertexSet()) {
        yPercent = getYpercent(vertex->getInfo());
        xPercent = getXpercent(vertex->getInfo());

        gv->addNode(vertex->getId(), (int)(xPercent*gv_width), (int)(yPercent*gv_height));
        gv->setVertexSize(vertex->getId(), 3);
//        gv->setVertexLabel(vertex->getId(), to_string(vertex->getId()));
    }

    int id = 0;
    for (Vertex<coordinates>* vertex : graph->getVertexSet()) {
        for (Edge<coordinates>* edge : vertex->getAdj()) {
            gv->addEdge(id, vertex->getId(), edge->getDest()->getId(), EdgeType::UNDIRECTED);
//            gv->setEdgeLabel(id, to_string(edge->getCost()));
            id++;
        }
    }

    enterWait();
    delete gv;
}

void UI::showPath(vector<int> path) {
    this->gv = new GraphViewer(gv_width, gv_height, false);
    gv->defineEdgeCurved(false);
    gv->defineVertexSize(5);
    gv->createWindow(gv_width, gv_height);
    for (int i = 0; i < path.size() - 1; i++) {
        Vertex<coordinates>* a = graph->findVertex(path.at(i));
        Vertex<coordinates>* b = graph->findVertex(path.at(i+1));
        gv->addNode(i, (int)(getXpercent(a->getInfo()) * gv_width), (int)(getYpercent(a->getInfo()) * gv_height));
//        gv->setVertexLabel(i, to_string(a->getId()));
        gv->addNode(i+1, (int)(getXpercent(b->getInfo()) * gv_width), (int)(getYpercent(b->getInfo()) * gv_height));
//        gv->setVertexLabel(i+1, to_string(b->getId()));
        gv->addEdge(i, i, i+1, EdgeType::UNDIRECTED);
//        gv->setEdgeLabel(i, to_string(a->getCostTo(b->getId())));
    }
    gv->rearrange();

    enterWait();
    delete gv;
}

double UI::getXpercent(const coordinates &c) const {
    return (c.first - graph->getMinCoords().first) /
            (graph->getMaxCoords().first - graph->getMinCoords().first) * 0.9 + 0.05;
}

double UI::getYpercent(const coordinates &c) const {
    return 1.0 - ((c.second - graph->getMinCoords().second) /
            (graph->getMaxCoords().second - graph->getMinCoords().second) * 0.9 + 0.05);
}
