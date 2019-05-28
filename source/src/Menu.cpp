//
// Created by david on 27-05-2019.
//

#include "Menu.h"


string cityName;
GraphViewer *gv = NULL;
Graph wholeMapGraph, graphAfterDFS, fwGraph;
Person driver = Person(0, "Default");
unsigned int driverDestNodeID = -1, driverSrcNodeID=1052802949;
const long long MAX_STREAM_SIZE = numeric_limits<streamsize>::max();
vector<Person> passengersRes;
bool generated = false;
vector<NodeInfo> path;

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
    cout << " 7- Run Algorithm " << endl;
    cout << " 8- Check complexity " << endl;
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

                showWholeMap();
                break;
            case 6:

                exit = showDFSAfterDriver();
                break;
                /**

            case 7:
                checkAlgorithm();
                break;
            case 8:

                initViewer(true);

                cout << "Starting graph processing..." << endl;
                graphAfterDFS.processGraph(fwGraph);
                cout << "Done." << endl;
                loadGraphForVis(gv, fwGraph);

                cin >> tempChar;
                cin.ignore(MAX_STREAM_SIZE, '\n');
                gv->closeWindow();

                break;

                 **/
            case 7:
                checkAlgorithm();
                break;
            case 8:
                checkComplexity();
                break;

            case 0:
                exit = true;
                break;
        }

    }

}

void chooseDriver() {

    unsigned int startNodeID, endNodeID, startHour,startMinute,endHour,endMinute;
    string driverName;

    cout << "-- Driver Selection --" << endl << endl;

    cout << "Driver name: ";

    getline(cin, driverName);

    cout << "Start node ID: ";
    cin >> startNodeID;

    if (!generated) {

        cout << "End node ID (must be the same as the destinations of the people in graph): ";
        cin >> endNodeID;
        driverDestNodeID = endNodeID;
    }

    cin.ignore(MAX_STREAM_SIZE, '\n');
/*
    driver = Person(100000000,driverName);
    driver.setNodes(startNodeID,endNodeID);
    driver.setTimes(Time(00,00,00), Time(23,59,00));
    Vertex *startVertex = wholeMapGraph.findVertex(NodeInfo(startNodeID)); //add driver to graph
    startVertex->getInfoRef().addPerson(driver);
*/
    cout << "Start hour and minute: ";
    cin >> startHour >> startMinute;

    cout << "End hour and minute: ";
    cin >> endHour >> endMinute;

    driver = Person(-1, driverName);
    driver.setNodes(startNodeID, driverDestNodeID);
    driver.setTimes(Time(startHour,startMinute),Time(endHour,endMinute));
    Vertex *startVertex = wholeMapGraph.findVertex(NodeInfo(startNodeID)); //add driver to graph
    startVertex->getInfoRef().addPerson(driver);

}

void chooseCity() {

    cout << "Please enter a city: ";
    getline(cin, cityName);
    cout << "Loading Map to graph..." << endl;
    wholeMapGraph.loadFromFile(cityName);
    cout << "Done." << endl;
}

void initViewer(bool autoPosition) {

    delete (gv);
    gv = new GraphViewer(10000, 10000, autoPosition);
    gv->defineVertexColor("blue");
    gv->defineEdgeColor("black");
    gv->createWindow(1200, 1200);

}

void generatePeople() {

    int amount;
    cout << "How many people ";
    cin >> amount;
    cin.ignore(MAX_STREAM_SIZE, '\n');
    driverDestNodeID = genPeople(amount, cityName);
    cout << "Done." << endl;
    generated = true;
}



void checkAlgorithm() {

    cout << "Starting DFS on driver node" << endl;
    wholeMapGraph.dfs(NodeInfo(driver.getSourceNodeID()));
    cout << "Done." << endl;

    Vertex *destVertex = wholeMapGraph.findVertex(NodeInfo(driverDestNodeID));

    if (!destVertex->isVisited()) {

        cout << "The driver's destination isn't reachable from his starting position. Exiting..." << endl;
        return;
    }

    cout << "Building achievable from driver graph..." << endl;
    wholeMapGraph.buildAchievableGraph(graphAfterDFS);
    cout << "Done." << endl;
    Graph graph3;
    cout << "Processing graph..." << endl;
    graphAfterDFS.processGraph(graph3,driver);
    cout << "Done." << endl;
    Car car1=Car(0,4,driver);

    cout << "Starting fillCarGreedy" << endl;
    vector<Person> passengers=car1.fillCarGreedy(&graph3, 5000);
    cout << "Done." << endl;


    cout<< "Passengers:"<<endl;
    for(auto p: passengers)
        cout<< "Passenger id: " <<p.getID()<<", name: "<< p.getName() << " minTime " << p.getMinDepartureTime() << " maxTime " << p.getMaxArrivalTime() << " pickupTime " << p.getPickupTime() << endl;

    passengersRes = passengers;

    path = graphAfterDFS.getPath(passengers);

}

void showWholeMap() {

    char tempChar;
    initViewer();
    cout << "Loading whole graph for Vis..." << endl;
    loadGraphForVis(gv, wholeMapGraph);


    for(int i = 0; i < path.size();i++){

        gv->setVertexColor(wholeMapGraph.findVertex(path.at(i))->getInfo().getID(),"DARK_GRAY");
    }

    for(int i = 0; i < passengersRes.size();i++){

        gv->setVertexColor(passengersRes.at(i).getSourceNodeID(),"GREEN");
    }


    if(driver.getName() != "Default"){

        gv->setVertexColor(driver.getSourceNodeID(), "PINK");
        gv->setVertexColor(driverDestNodeID, "MAGENTA");
    }

    cout << "Done." << endl;
    cin >> tempChar;
    cin.ignore(MAX_STREAM_SIZE, '\n');
    gv->closeWindow();
}

bool showDFSAfterDriver() {

    char tempChar;
    initViewer();

    cout << "Starting DFS..." << endl;
    wholeMapGraph.dfs(NodeInfo(driver.getSourceNodeID()));
    cout << "Done." << endl;
    cout << "Building achievable graph..." << endl;


    Vertex *destVertex = wholeMapGraph.findVertex(NodeInfo(driverDestNodeID));

    if (!destVertex->isVisited()) {

        cout << "The driver's destination isn't reachable from his starting position. Exiting..." << endl;
        return true;
    }

    wholeMapGraph.buildAchievableGraph(graphAfterDFS);
    cout << "Done." << endl;

    cout << "Loading achievable graph for Vis..." << endl;
    loadGraphForVis(gv, graphAfterDFS);
    cout << "Done." << endl;
    gv->setVertexColor(driver.getSourceNodeID(), "PINK");
    gv->setVertexColor(driverDestNodeID, "MAGENTA");
    cin >> tempChar;
    cin.ignore(MAX_STREAM_SIZE, '\n');
    gv->closeWindow();

    return false;
}

void checkComplexity(){
    ofstream complexityPerson;
    complexityPerson.open ("../resources/complexityPerson.csv");
    //driverDestNodeID = genPeople(1000000, cityName);
    driverDestNodeID=1052802902;
    driver.setNodes(driverSrcNodeID,driverDestNodeID);
    driver.setTimes(Time(8,30),Time(12,30));
    Vertex *startVertex = wholeMapGraph.findVertex(NodeInfo(driverSrcNodeID)); //add driver to graph
    startVertex->getInfoRef().addPerson(driver);
    for(int i= 0; i<18; i++){
        wholeMapGraph.loadPeople(i*30000, (i+1)*30000);
        clock_t tStart = clock();
        checkAlgorithm();
        complexityPerson<<i<<";"<<(double)(clock() - tStart)/CLOCKS_PER_SEC<<endl;
    }
    complexityPerson.close();
}
