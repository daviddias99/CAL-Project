
#include "PersonGen.h"

int randomBetween(int a, int b){

    return rand() %  (b-a) + a;
}

#define MAP_FOLDER_PATH "../resources/mapas/"
#define EDGE_FILE_PATH "/T01_edges_"
#define NODE_XY_FILE_PATH "/T01_nodes_X_Y_"
#define NODE_LL_FILE_PATH "/T01_nodes_lat_lon_"

unsigned int genPeople(unsigned int amount, string cidade) {

    vector<string> names;

    ifstream nameFile,nodeFile;
    ofstream output;
    string nodePath;

    ostringstream nodePath_XY;
    nodePath_XY << MAP_FOLDER_PATH << cidade << NODE_XY_FILE_PATH << cidade << ".txt";
    nodePath = nodePath_XY.str();

    nameFile.open("../resources/person_names.txt");
    nodeFile.open(nodePath);

    string outputFileName = "../resources/persons_" + cidade + ".txt";
    output.open(outputFileName);

    srand(time(NULL));

    while(!nameFile.eof()){

        string line;

        getline(nameFile,line);

        names.push_back(line);
    }

    string nodeCnt;
    getline(nodeFile,nodeCnt);

    vector<unsigned int> nodeIDs;

    while (!nodeFile.eof()) {

        string currentLine;

        getline(nodeFile, currentLine);
        stringstream line(currentLine);

        char tempChar;
        unsigned int ID;

        line >> tempChar >> ID;

        nodeIDs.push_back(ID);
    }

    int destID = nodeIDs.at(randomBetween(0,nodeIDs.size()-1));

    for(int i = 0; i < amount; i++){

        string newLine = "( " + to_string(i) + " , ";

        int hour1 = randomBetween(6,21);
        int minute1 = randomBetween(0,59);
        int delay = randomBetween(60,120);

        int hour2 = hour1 +(minute1 + delay) / 60;
        int minute2 = (minute1 + delay) % 60;

        newLine += names.at(randomBetween(0,names.size()-1)) + " , ";

        if(minute1 < 10)
            newLine += to_string(hour1) + ":" + "0"+to_string(minute1) + " , ";
        else
            newLine += to_string(hour1) + ":" + to_string(minute1) + " , ";
        newLine += to_string(hour2) + ":" + to_string(minute2) + " , ";
        newLine += to_string(nodeIDs.at(randomBetween(0,nodeIDs.size()-1))) + " , " + to_string(destID)  + " )";

        output << newLine << endl;
    }

    return destID;
}