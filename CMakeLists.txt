cmake_minimum_required(VERSION 3.15)
project(Proj)

set(CMAKE_CXX_STANDARD 14)

# The line below is necessary if you are under Windows only
# Comment the line below if you are under Linux or Mac OS
if (MINGW)
    link_libraries(ws2_32 wsock32)
endif ()


include_directories(src)
include_directories(maps)

add_executable(Proj main.cpp src/Graph/Graph.cpp src/Graph/Graph.h src/UI/UI.cpp src/UI/UI.h src/UI/Menu.cpp src/UI/Menu.h
        src/Utils/Utils.cpp src/Utils/Utils.h src/GraphViewer/connection.cpp src/GraphViewer/connection.h
        src/GraphViewer/edgetype.h src/GraphViewer/graphviewer.cpp src/GraphViewer/graphviewer.h src/Utils/MapParser.cpp
        src/Utils/MapParser.h src/Graph/Path.cpp src/Graph/Path.h src/Utils/MenuUtils.cpp src/Utils/MenuUtils.h
        src/Utils/PerformanceTesting.cpp src/Utils/PerformanceTesting.h src/Context/Farm.cpp src/Context/Farm.h
        src/Context/Truck.cpp src/Context/Truck.h src/Context/Basket.cpp src/Context/Basket.h src/Context/Client.cpp
        src/Context/Client.h src/Graph/Route.cpp src/Graph/Route.h)
