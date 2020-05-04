#ifndef PROJ_UI_H
#define PROJ_UI_H

#include "../Graph/Graph.h"
#include "../GraphViewer/graphviewer.h"

using namespace std;


class UI {
private:
    Graph<int> graph;
    GraphViewer *gv;

    int gv_width;
    int gv_height;
public:
    UI(Graph<int> &graph, int width, int height);

    void setGraph(Graph<int> &graph);
    void showGraph();
};


#endif //PROJ_UI_H
