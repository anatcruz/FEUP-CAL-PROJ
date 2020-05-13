#ifndef PROJ_PATH_H
#define PROJ_PATH_H

#include <vector>

using namespace std;

class Path {
    double length;
    vector<int> path;
public:
    Path();
    Path(double length, const vector<int> &path);

    double getLength() const;

    vector<int> getPath() const;
    int getLastNode() const;

    void joinPath(const Path &p);

    void addNode(const int &id);
};


#endif //PROJ_PATH_H
