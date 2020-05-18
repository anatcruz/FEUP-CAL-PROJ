cmake_minimum_required(VERSION 3.15)
project(Proj)

set(CMAKE_CXX_STANDARD 14)
find_package (Threads)

# The line below is necessary if you are under Windows only
# Comment the line below if you are under Linux or Mac OS
#link_libraries(ws2_32 wsock32)

include_directories(src)
include_directories(maps)

add_executable(Proj main.cpp src/Graph/Graph.cpp src/Graph/Graph.h src/UI/UI.cpp src/UI/UI.h src/UI/Menu.cpp src/UI/Menu.h
        src/Utils/Utils.cpp src/Utils/Utils.h src/GraphViewer/connection.cpp src/GraphViewer/connection.h
        src/GraphViewer/edgetype.h src/GraphViewer/graphviewer.cpp src/GraphViewer/graphviewer.h src/Utils/MapParser.cpp src/Utils/MapParser.h src/Graph/Path.cpp src/Graph/Path.h src/Utils/MenuUtils.cpp src/Utils/MenuUtils.h src/Utils/PerformanceTesting.cpp src/Utils/PerformanceTesting.h)

target_link_libraries (Proj ${CMAKE_THREAD_LIBS_INIT})