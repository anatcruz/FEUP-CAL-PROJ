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

    Graph<coordinates> graph;
    UI ui = UI(&graph, 1900, 1000);
    vector<int> last_path;
    Farm farm;
    loadGraph(graph, farm, last_path, "../maps/GridGraphs/custom/4x4/nodes.txt", "../maps/GridGraphs/custom/4x4/edges.txt", true);

    Menu mainMenu("FarmFresh2U");
    Menu graphLoadMenu("Load graph", false);
    Menu shortestPathMenu("Shortest Path");
    Menu deliveryPathMenu("Delivery Path");
    Menu connectivityMenu("Graph connectivity");
    Menu performanceMenu("Performance");
    Menu managementMenu("Farm Management");
    Menu clientManagementMenu("Client Management");
    Menu basketManagementMenu("Basket Management");
    Menu truckManagementMenu("Truck Management");

    mainMenu.addOption("Exit", EXIT);
    mainMenu.addOption("Load graph", [&](){ graphLoadMenu.start(); });
    mainMenu.addOption("Show graph", [&](){ ui.showGraph(); });
    mainMenu.addOption("Pathfind", [&](){ shortestPathMenu.start(); });
    mainMenu.addOption("Delivery path", [&](){ deliveryPathMenu.start(); });
    mainMenu.addOption("Connectivity", [&](){ connectivityMenu.start(); });
    mainMenu.addOption("Performance", [&](){ performanceMenu.start(); });
    mainMenu.addOption("Farm Management", [&](){ managementMenu.start(); });

    graphLoadMenu.addOption("Go back", EXIT);
    graphLoadMenu.addOption("Porto Full", [&](){ loadGraph(graph, farm, last_path, "../maps/PortoMap/porto_full_nodes_xy.txt", "../maps/PortoMap/porto_full_edges.txt", false); });
    graphLoadMenu.addOption("Porto Strong", [&](){ loadGraph(graph, farm, last_path, "../maps/PortoMap/porto_strong_nodes_xy.txt", "../maps/PortoMap/porto_strong_edges.txt", true);});
    graphLoadMenu.addOption("4x4", [&](){ loadGraph(graph, farm, last_path, "../maps/GridGraphs/custom/4x4/nodes.txt", "../maps/GridGraphs/custom/4x4/edges.txt", true); });
    graphLoadMenu.addOption("8x8", [&](){ loadGraph(graph, farm, last_path, "../maps/GridGraphs/custom/8x8/nodes.txt", "../maps/GridGraphs/custom/8x8/edges.txt", true); });
    graphLoadMenu.addOption("8x8 with problem context", [&](){ loadGraph(graph, farm, last_path, "../maps/GridGraphs/custom/8x8/nodes.txt", "../maps/GridGraphs/custom/8x8/edges.txt", true,"../maps/GridGraphs/custom/8x8/data/farm.txt", "../maps/GridGraphs/custom/8x8/data/clients.txt"); });
    graphLoadMenu.addOption("16x16", [&](){ loadGraph(graph, farm, last_path, "../maps/GridGraphs/16x16/nodes.txt", "../maps/GridGraphs/16x16/edges.txt", true); });

    shortestPathMenu.addOption("Go back", EXIT);
    shortestPathMenu.addOption("Dijkstra", [&](){ dijkstra(graph, ui); });
    shortestPathMenu.addOption("Dijkstra Bi-Directional", [&](){ dijkstraBiDir(graph, ui); });
    shortestPathMenu.addOption("A-star", [&](){ astar(graph, ui); });
    shortestPathMenu.addOption("A-star Bi-Directional", [&](){ astarBiDir(graph, ui); });

    deliveryPathMenu.addOption("Go back", EXIT);
    deliveryPathMenu.addOption("Make delivery route", [&](){ solveTSPwithContext(graph, ui, farm); });
    deliveryPathMenu.addOption("Make delivery route with different trucks", [&](){ solveVRPsweep(graph, ui, farm); });
    deliveryPathMenu.addOption("General TSP", [&](){ solveTSPnoContext(graph, ui); });

    connectivityMenu.addOption("Go back", [&](){});
    connectivityMenu.addOption("View largest SCC", [&](){ last_path = largestSCC(graph, ui); });
    connectivityMenu.addOption("Make graph largest SCC", [&](){ graph.makePathGraph(last_path); });

    performanceMenu.addOption("Go back", [&](){});
    performanceMenu.addOption("Dijkstra performance", [&](){ dijkstraPerfTest(graph); });
    performanceMenu.addOption("Dijkstra Bi-Directional performance", [&](){ dijkstraBiDirPerfTest(graph); });
    performanceMenu.addOption("A-star performance", [&](){ astarPerfTest(graph); });
    performanceMenu.addOption("A-star Bi-Directional performance", [&](){ astarBiDirPerfTest(graph); });
    performanceMenu.addOption("Clear log", [&](){ clearLog(); });

    managementMenu.addOption("Go back", [&](){});
    managementMenu.addOption("Client Management", [&](){ clientManagementMenu.start(); });
    managementMenu.addOption("Basket Management", [&](){ basketManagementMenu.start(); });
    managementMenu.addOption("Truck Management", [&](){ truckManagementMenu.start(); });

    clientManagementMenu.addOption("Go back", [&](){});
    clientManagementMenu.addOption("List clients", [&](){ showClientList(farm); });
    clientManagementMenu.addOption("Create client", [&](){ farm.createClient(graph); });
    clientManagementMenu.addOption("Edit client", [&](){ farm.editClient(graph); });
    clientManagementMenu.addOption("Remove client", [&](){ farm.removeClient(graph); });

    basketManagementMenu.addOption("Go back", [&](){});
    basketManagementMenu.addOption("List baskets", [&](){ showBasketList(farm); });
    basketManagementMenu.addOption("Create basket", [&](){ farm.createBasket(); });
    basketManagementMenu.addOption("Edit basket", [&](){ farm.editBasket(); });
    basketManagementMenu.addOption("Remove basket", [&](){ farm.removeBasket(); });

    truckManagementMenu.addOption("Go back", [&](){});
    truckManagementMenu.addOption("List trucks", [&](){ showTruckList(farm); });
    truckManagementMenu.addOption("Create truck", [&](){ farm.createTruck(); });
    truckManagementMenu.addOption("Edit truck", [&](){ farm.editTruck(); });
    truckManagementMenu.addOption("Remove truck", [&](){ farm.removeTruck(); });

    mainMenu.start();

    return 0;
}
