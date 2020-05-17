#include <csignal>

#include "Graph/Graph.h"
#include "UI/UI.h"
#include "UI/Menu.h"
#include "Utils/MapParser.h"
#include "Utils/MenuUtils.h"
#include "Utils/PerformanceTesting.h"

int main() {
    signal(SIGINT, SIG_IGN);
    srand(time(NULL));

    Graph<coordinates> graph = parseGridMap("../maps/GridGraphs/custom/4x4/nodes.txt", "../maps/GridGraphs/custom/4x4/edges.txt", true);;
    UI ui = UI(&graph, 1200, 800);

    Menu mainMenu("FarmFresh2U");
    Menu graphLoadMenu("Load graph");
    Menu shortestPathMenu("Shortest Path");
    Menu connectivityMenu("Graph connectivity");
    Menu performanceMenu("Performance");

    mainMenu.addOption("Exit", [&](){});
    mainMenu.addOption("Load graph", [&](){ graphLoadMenu.start(); });
    mainMenu.addOption("Show graph", [&](){ ui.showGraph(); });
    mainMenu.addOption("Pathfind", [&](){ shortestPathMenu.start(); });
    mainMenu.addOption("Connectivity", [&](){ connectivityMenu.start(); });
    mainMenu.addOption("Performance", [&](){ performanceMenu.start(); });

    graphLoadMenu.addOption("Go back", [&](){});
    graphLoadMenu.addOption("Porto", [&](){ graph = parseGridMap("../maps/PortugalMaps/Porto/nodes_x_y_porto.txt", "../maps/PortugalMaps/Porto/edges_porto.txt", false); });
    graphLoadMenu.addOption("Lisboa", [&](){ graph = parseGridMap("../maps/PortugalMaps/Lisboa/nodes_x_y_lisboa.txt", "../maps/PortugalMaps/Lisboa/edges_lisboa.txt", false); });
    graphLoadMenu.addOption("4x4", [&](){ graph = parseGridMap("../maps/GridGraphs/custom/4x4/nodes.txt", "../maps/GridGraphs/custom/4x4/edges.txt", true); });
    graphLoadMenu.addOption("8x8", [&](){ graph = parseGridMap("../maps/GridGraphs/8x8/nodes.txt", "../maps/GridGraphs/8x8/edges.txt", true); });
    graphLoadMenu.addOption("16x16", [&](){ graph = parseGridMap("../maps/GridGraphs/16x16/nodes.txt", "../maps/GridGraphs/16x16/edges.txt", true); });

    shortestPathMenu.addOption("Go back", [&](){});
    shortestPathMenu.addOption("Dijkstra", [&](){ dijkstra(graph, ui); });
    shortestPathMenu.addOption("A-star", [&](){ astar(graph, ui); });

    connectivityMenu.addOption("Go back", [&](){});
    connectivityMenu.addOption("View largest SCC", [&](){ largestSCC(graph, ui); });

    performanceMenu.addOption("Go back", [&](){});
    performanceMenu.addOption("Dijkstra performance", [&](){ dijkstraPerfTest(graph); });

    mainMenu.start();

    return 0;
}
