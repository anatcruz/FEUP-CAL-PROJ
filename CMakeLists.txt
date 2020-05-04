cmake_minimum_required(VERSION 3.16)
project(Proj)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(Proj main.cpp src/Graph/Graph.h src/UI/UI.cpp src/UI/UI.h src/UI/Menu.cpp src/UI/Menu.h
        src/Utils/Utils.cpp src/Utils/Utils.h src/GraphViewer/connection.cpp src/GraphViewer/connection.h
        src/GraphViewer/edgetype.h src/GraphViewer/graphviewer.cpp src/GraphViewer/graphviewer.h)