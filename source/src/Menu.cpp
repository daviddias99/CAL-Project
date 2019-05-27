//
// Created by david on 27-05-2019.
//

#include <graph_viz/graphviewer.h>
#include "Menu.h"
#include "Graph.h"
#include "PersonGen.h"
#include "VisLoader.h"
#include "Car.h"

string cityName;
GraphViewer* gv = NULL;
Graph wholeMapGraph, graphAfterDFS, fwGraph;
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
        char tempChar;
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

                initViewer();
                cout << "Loading whole graph for Vis..." << endl;
                loadGraphForVis(gv,wholeMapGraph);
                cout << "Done." << endl;
                cin >> tempChar;
                cin.ignore(MAX_STREAM_SIZE, '\n');
                gv->closeWindow();
                break;
            case 6:

                initViewer();

                cout << "Starting DFS..." << endl;
                wholeMapGraph.dfs(NodeInfo(driver.getSourceNodeID()));
                cout << "Done." << endl;
                cout << "Building achievable graph..." << endl;
                wholeMapGraph.buildAchievableGraph(graphAfterDFS);
                cout << "Done." << endl;

                cout << "Loading achievable graph for Vis..." << endl;
                loadGraphForVis(gv,graphAfterDFS);
                cout << "Done." << endl;

                cin >> tempChar;
                cin.ignore(MAX_STREAM_SIZE, '\n');
                gv->closeWindow();
                break;
                /**
            case 7:

                initViewer(true);

                cout << "Starting graph processing..." << endl;
                graphAfterDFS.processGraph(fwGraph);
                cout << "Done." << endl;
                loadGraphForVis(gv,fwGraph);

                cin >> tempChar;
                cin.ignore(MAX_STREAM_SIZE, '\n');
                gv->closeWindow();

                break;
                 **/
            case 7:
                checkAlgorithm();


                break;
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
    cin.ignore(MAX_STREAM_SIZE, '\n');
    driver = Person(100000000,driverName);
    driver.setNodes(startNodeID,endNodeID);
    driver.setTimes(Time(00,00,00), Time(23,59,00));
    Vertex *startVertex = wholeMapGraph.findVertex(NodeInfo(startNodeID)); //add driver to graph
    startVertex->getInfoRef().addPerson(driver);
}

void chooseCity() {

    cout << "Please enter a city: ";
    getline(cin,cityName);
    cout << "Loading Map to graph..." << endl;
    wholeMapGraph.loadFromFile(cityName);
    cout << "Done." << endl;
}

void initViewer(bool autoPosition) {

    delete(gv);
    gv = new GraphViewer(10000, 10000, autoPosition);
    gv->defineVertexColor("blue");
    gv->defineEdgeColor("black");
    gv->createWindow(1200, 1200);

}

void generatePeople(){

    int amount;
    cout << "How many people ";
    cin >> amount;
    cin.ignore(MAX_STREAM_SIZE, '\n');
    genPeople(amount,cityName);
    cout << "Done." << endl;
}

void checkAlgorithm(){

    wholeMapGraph.dfs(NodeInfo(driver.getSourceNodeID()));
    wholeMapGraph.buildAchievableGraph(graphAfterDFS);
    Graph graph3;
    graphAfterDFS.processGraph(graph3);
    Car car1=Car(0,4,driver);

    vector<Person> passengers=car1.fillCarGreedy(&graph3, 10000);
    cout<< "Passengers:"<<endl;
    for(auto p: passengers)
        cout<< "Passenger id: " <<p.getID()<<", name: "<< p.getName()<<endl;

}