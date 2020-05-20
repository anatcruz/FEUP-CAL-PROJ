#include "UI.h"

UI::UI(Graph<coordinates> *graph, int width, int height) : graph(graph), gv_width(width), gv_height(height) {}

void UI::setGraph(Graph<coordinates> *graph) { this->graph = graph; }

void UI::showGraph() {
    this->gv = new GraphViewer(gv_width, gv_height, false);
    gv->defineEdgeCurved(false);
    gv->createWindow(gv_width, gv_height);

    for (Vertex<coordinates>* vertex : graph->getVertexSet()) {
        gv->addNode(vertex->getId(), x_fitted(vertex->getInfo().first), y_fitted(vertex->getInfo().second));
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
    gv->addNode(0, x_fitted(a->getInfo().first), y_fitted(a->getInfo().second));
//    gv->setVertexLabel(0, to_string(a->getId()));
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

        gv->addNode(i, x_fitted(a->getInfo().first), y_fitted(a->getInfo().second));
        gv->addEdge(i, i-1, i, EdgeType::DIRECTED);
//        gv->setVertexLabel(i, to_string(a->getId()));
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

int UI::x_fitted(double x) {
    return (x - graph->getMinCoords().first) * (gv_width - 50) / (graph->getMaxCoords().first - graph->getMinCoords().first) + 25;
}

int UI::y_fitted(double y) {
    return (y - graph->getMinCoords().second) * (gv_height - 50) / (graph->getMaxCoords().second - graph->getMinCoords().second) + 25;
}

