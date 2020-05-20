#ifndef PROJ_UI_H
#define PROJ_UI_H

#include "../Graph/Graph.h"
#include "../GraphViewer/graphviewer.h"

using namespace std;


class UI {
private:
    Graph<coordinates> *graph;
    GraphViewer *gv;

    int gv_width;
    int gv_height;

    int x_fitted(double x);
    int y_fitted(double y);
public:
    UI(Graph<coordinates> *graph, int width, int height);

    void setGraph(Graph<coordinates> *graph);
    void showGraph();
    void showPath(vector<int> path);
};


#endif //PROJ_UI_H
