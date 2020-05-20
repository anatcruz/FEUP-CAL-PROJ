#include <csignal>

#include "Graph/Graph.h"
#include "Context/Farm.h"
#include "UI/UI.h"
#include "UI/Menu.h"
#include "Utils/MapParser.h"
#include "Utils/MenuUtils.h"
#include "Utils/PerformanceTesting.h"

int main() {
    signal(SIGINT, SIG_IGN);
    srand(time(NULL));

    Graph<coordinates> graph = parseGridMap("../maps/GridGraphs/custom/4x4/nodes.txt", "../maps/GridGraphs/custom/4x4/edges.txt", true);;
    UI ui = UI(&graph, 1900, 1000);
    vector<int> last_path;
    Farm farm;

    Menu mainMenu("FarmFresh2U");
    Menu graphLoadMenu("Load graph", false);
    Menu shortestPathMenu("Shortest Path");
    Menu deliveryPathMenu("Delivery Path");
    Menu connectivityMenu("Graph connectivity");
    Menu performanceMenu("Performance");

    mainMenu.addOption("Exit", EXIT);
    mainMenu.addOption("Load graph", [&](){ graphLoadMenu.start(); });
    mainMenu.addOption("Show graph", [&](){ ui.showGraph(); });
    mainMenu.addOption("Pathfind", [&](){ shortestPathMenu.start(); });
    mainMenu.addOption("Delivery path", [&](){ deliveryPathMenu.start(); });
    mainMenu.addOption("Connectivity", [&](){ connectivityMenu.start(); });
    mainMenu.addOption("Performance", [&](){ performanceMenu.start(); });

    graphLoadMenu.addOption("Go back", EXIT);
    graphLoadMenu.addOption("Porto Full", [&](){ graph = parseGridMap("../maps/PortoMap/porto_full_nodes_xy.txt", "../maps/PortoMap/porto_full_edges.txt", false); last_path.clear(); });
    graphLoadMenu.addOption("Porto Strong", [&](){ graph = parseGridMap("../maps/PortoMap/porto_strong_nodes_xy.txt", "../maps/PortoMap/porto_strong_edges.txt", true); last_path.clear(); });
    graphLoadMenu.addOption("4x4", [&](){ graph = parseGridMap("../maps/GridGraphs/custom/4x4/nodes.txt", "../maps/GridGraphs/custom/4x4/edges.txt", true); last_path.clear(); });
    graphLoadMenu.addOption("8x8", [&](){ graph = parseGridMap("../maps/GridGraphs/custom/8x8/nodes.txt", "../maps/GridGraphs/custom/8x8/edges.txt", true); last_path.clear(); });
    graphLoadMenu.addOption("8x8 with problem context", [&](){ graph = parseGridMap("../maps/GridGraphs/custom/8x8/nodes.txt", "../maps/GridGraphs/custom/8x8/edges.txt", true); farm = loadContext(graph, "../maps/GridGraphs/custom/8x8/data/farm.txt", "../maps/GridGraphs/custom/8x8/data/clients.txt"); last_path.clear(); });
    graphLoadMenu.addOption("16x16", [&](){ graph = parseGridMap("../maps/GridGraphs/16x16/nodes.txt", "../maps/GridGraphs/16x16/edges.txt", true); last_path.clear(); });

    shortestPathMenu.addOption("Go back", EXIT);
    shortestPathMenu.addOption("Dijkstra", [&](){ dijkstra(graph, ui); });
    shortestPathMenu.addOption("Dijkstra Bi-Directional", [&](){ dijkstraBiDir(graph, ui); });
    shortestPathMenu.addOption("A-star", [&](){ astar(graph, ui); });
    shortestPathMenu.addOption("A-star Bi-Directional", [&](){ astarBiDir(graph, ui); });

    deliveryPathMenu.addOption("Go back", EXIT);
    deliveryPathMenu.addOption("List clients", [&](){ showClientList(graph, ui); });
    deliveryPathMenu.addOption("Make delivery route", [&](){ solveTSPwithContext(graph, ui, farm); });
    deliveryPathMenu.addOption("General TSP", [&](){});

    connectivityMenu.addOption("Go back", [&](){});
    connectivityMenu.addOption("View largest SCC", [&](){ last_path = largestSCC(graph, ui); });
    connectivityMenu.addOption("Make graph largest SCC", [&](){ graph.makePathGraph(last_path); });

    performanceMenu.addOption("Go back", [&](){});
    performanceMenu.addOption("Dijkstra performance", [&](){ dijkstraPerfTest(graph); });
    performanceMenu.addOption("Dijkstra Bi-Directional performance", [&](){ dijkstraBiDirPerfTest(graph); });
    performanceMenu.addOption("A-star performance", [&](){ astarPerfTest(graph); });
    performanceMenu.addOption("A-star Bi-Directional performance", [&](){ astarBiDirPerfTest(graph); });
    performanceMenu.addOption("Clear log", [&](){ clearLog(); });

    mainMenu.start();

    return 0;
}
