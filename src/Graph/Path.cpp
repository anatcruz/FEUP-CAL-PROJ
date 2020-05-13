//
// Created by antonio on 13/05/20.
//

#include "Path.h"

double Path::getLength() const {
    return length;
}

vector<int> Path::getPath() const {
    return path;
}

void Path::joinPath(const Path &p) {
    this->length += p.length;
    this->path.insert(path.end(), p.path.begin() + 1, p.path.end());
}

void Path::addNode(const int &id) {
    this->path.push_back(id);
}

Path::Path() {
    this->length = 0;
    this->path = vector<int>();
}

Path::Path(double length, const vector<int> &path) : length(length), path(path) {}

int Path::getLastNode() const {
    return path.back();
}


