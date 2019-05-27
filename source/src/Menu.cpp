//
// Created by david on 27-05-2019.
//

#include <graph_viz/graphviewer.h>
#include "Menu.h"
#include "Graph.h"
#include "PersonGen.h"
#include "VisLoader.h"

string cityName;
GraphViewer* gv;
Graph wholeMapGraph, graphAfterDFS;
Person driver = Person(0,"Default");
const long long MAX_STREAM_SIZE = numeric_limits<streamsize>::max();

void showMainMenu() {


    cout << " <<<<<<<< CAL - RIDESHARING >>>>>>>>" << endl << endl;
    cout << "\t\t" << "        _______" << endl;
    cout << "\t\t" << "       //  ||\\ \\" << endl;
    cout << "\t\t" << " _____//___||_\\ \\___" << endl;
    cout << "\t\t" << " )  _          _    \\" << endl;
    cout << "\t\t" << " |_/ \\________/ \\___|" << endl;
    cout << "\t\t" << "___\\_/________\\_/______" << endl << endl;

    cout << " 1- Choose city" << endl;
    cout << " 2- Generate people" << endl;
    cout << " 3- Add people to graph" << endl;
    cout << " 4- Choose driver info" << endl;
    cout << " 5- Show whole map" << endl;
    cout << " 6- Show graph after driver DFS" << endl;
    cout << " 7- Run Algorithm "<< endl;
    cout << " 0- Exit" << endl;

    cout << endl;
    cout << "Option:";


}

void runMainMenu() {

    bool exit = false;

    while (!exit) {

        showMainMenu();

        int option;
        cin >> option;
        cin.ignore(MAX_STREAM_SIZE, '\n');
        switch (option) {

            case 1:
                chooseCity();
                break;
            case 2:
                generatePeople();
                break;
            case 3:
                wholeMapGraph.loadPeople();
                break;
            case 4:

                chooseDriver();
                break;
            case 5:

                delete(gv);
                initViewer();

                gv->createWindow(1200, 1200);
                cout << "Loading whole graph for Vis..." << endl;
                loadGraphForVis(gv,wholeMapGraph);
                cout << "Done." << endl;
                getchar();
                gv->closeWindow();
                break;
            case 6:
                delete(gv);
                initViewer();

                cout << "Starting DFS..." << endl;
                wholeMapGraph.dfs(NodeInfo(driver.getSourceNodeID()));
                cout << "Done." << endl;
                cout << "Building achievable graph..." << endl;
                graphAfterDFS = wholeMapGraph.buildAchievableGraph();
                cout << "Done." << endl;
                gv->createWindow(1200, 1200);
                cout << "Loading achievable graph for Vis..." << endl;
                loadGraphForVis(gv,graphAfterDFS);
                cout << "Done." << endl;

                getchar();
                gv->closeWindow();
            case 0:
                exit = true;
                break;
        }

    }

}

void chooseDriver() {

    unsigned int startNodeID,endNodeID;
    string driverName;

    cout << "-- Driver Selection --" << endl << endl;

    cout << "Driver name: ";

    getline(cin,driverName);

    cout << "Start node ID: ";
    cin >>startNodeID;

    cout << "End node ID: ";
    cin >> endNodeID;

    driver = Person(100000000,driverName);
    driver.setNodes(startNodeID,endNodeID);
}

void chooseCity() {

    cout << "Please enter a city: ";
    getline(cin,cityName);
    cout << "Loading Map to graph..." << endl;
    wholeMapGraph.loadFromFile(cityName);
    cout << "Done." << endl;
}

void initViewer(bool autoPosition) {

    gv = new GraphViewer(10000, 10000, autoPosition);
    gv->defineVertexColor("blue");
    gv->defineEdgeColor("black");


}

void generatePeople(){

    int amount;
    cout << "How many people ";
    cin >> amount;
    cin.ignore(MAX_STREAM_SIZE, '\n');
    genPeople(amount,cityName);
    cout << "Done." << endl;
}
