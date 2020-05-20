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
        switch (vertex->tag) {
            case quinta:
                gv->setVertexSize(vertex->getId(), 10);
                gv->setVertexColor(vertex->getId(), "BLUE");
                break;
            case garagem:
                gv->setVertexSize(vertex->getId(), 10);
                gv->setVertexColor(vertex->getId(), "ORANGE");
                break;
            case cliente:
                gv->setVertexSize(vertex->getId(), 10);
                gv->setVertexColor(vertex->getId(), "RED");
                break;
            case none:
                gv->setVertexSize(vertex->getId(), 3);
                gv->setVertexColor(vertex->getId(), "YELLOW");
                break;
        }

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
    gv->addNode(0, (int)(getXpercent(a->getInfo()) * gv_width), (int)(getYpercent(a->getInfo()) * gv_height));
    gv->setVertexLabel(0, to_string(a->getId()));
    switch (a->tag) {
        case quinta:
            gv->setVertexSize(0, 10);
            gv->setVertexColor(0, "BLUE");
            break;
        case garagem:
            gv->setVertexSize(0, 10);
            gv->setVertexColor(0, "ORANGE");
            break;
        case cliente:
            gv->setVertexSize(0, 10);
            gv->setVertexColor(0, "RED");
            break;
        case none:
            gv->setVertexSize(0, 3);
            gv->setVertexColor(0, "YELLOW");
            break;
    }

    for (int i = 1; i < path.size() - 1; i++) {
        a = graph->findVertex(path.at(i+1));

        gv->addNode(i, (int)(getXpercent(a->getInfo()) * gv_width), (int)(getYpercent(a->getInfo()) * gv_height));
        gv->addEdge(i, i-1, i, EdgeType::DIRECTED);
        gv->setVertexLabel(i, to_string(a->getId()));
        switch (a->tag) {
            case quinta:
                gv->setVertexSize(i, 10);
                gv->setVertexColor(i, "BLUE");
                break;
            case garagem:
                gv->setVertexSize(i, 10);
                gv->setVertexColor(i, "ORANGE");
                break;
            case cliente:
                gv->setVertexSize(i, 10);
                gv->setVertexColor(i, "RED");
                break;
            case none:
                gv->setVertexSize(i, 3);
                gv->setVertexColor(i, "YELLOW");
                break;
        }

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
