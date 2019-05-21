//
// Created by david on 21-05-2019.
//

#include "VisLoader.h"




void loadGraphForVis(GraphViewer* gv, string cidade) {

    int minX = INF;
    int minY = INF;

    ifstream nodeFile, edgeFile;
    string currentLine,nodePathStr_XY, nodePathStr_LL, edgePathStr;
    unsigned int ID = 0;

    ostringstream nodePath_XY;
    ostringstream nodePath_LL;
    ostringstream edgePath;

    nodePath_XY << MAP_FOLDER_PATH << cidade << NODE_XY_FILE_PATH << cidade << ".txt";
    nodePath_LL << MAP_FOLDER_PATH << cidade << NODE_LL_FILE_PATH << cidade << ".txt";
    edgePath << MAP_FOLDER_PATH << cidade << EDGE_FILE_PATH << cidade << ".txt";

    nodePathStr_XY = nodePath_XY.str();
    nodePathStr_LL = nodePath_LL.str();
    edgePathStr = edgePath.str();

    nodeFile.open(nodePathStr_XY);
    edgeFile.open(edgePathStr);

    getline(nodeFile, currentLine);



    while (!nodeFile.eof()) {

        getline(nodeFile, currentLine);
        stringstream line(currentLine);

        char tempChar;
        unsigned int ID;
        plotPos_t coords;

        line >> tempChar >> ID >> tempChar >> coords.x >> tempChar >> coords.y;

        if (coords.x < minX)
            minX = coords.x;

        if (coords.y < minY)
            minY = coords.y;

    }

    nodeFile.close();
    nodeFile.open(nodePathStr_XY);
    getline(nodeFile, currentLine);

    while (!nodeFile.eof()) {

        getline(nodeFile, currentLine);
        stringstream line(currentLine);

        char tempChar;
        unsigned int ID;
        plotPos_t coords;

        line >> tempChar >> ID >> tempChar >> coords.x >> tempChar >> coords.y;

        gv->addNode(ID, coords.x - minX, coords.y - minY);

    }

    getline(edgeFile, currentLine);

    while (!edgeFile.eof()) {

        getline(edgeFile, currentLine);
        stringstream line(currentLine);

        unsigned int IDSource, IDDest;
        char tempChar;

        line >> tempChar >> IDSource >> tempChar >> IDDest;

        gv->addEdge(ID, IDSource, IDDest, EdgeType::DIRECTED);
        ID++;
    }

    gv->rearrange();

    return;


}

void loadGraphForVis(GraphViewer* gv, Graph& graph) {

    vector<Vertex*> vSet = graph.getVertexSet();
    unsigned int id = 0;

    int minX = INF;
    int minY = INF;

    for (size_t i = 0; i < vSet.size(); i++) {

        Vertex * currVertex = vSet.at(i);

        double x = currVertex->getInfo().getPlotPos().x;
        double y = currVertex->getInfo().getPlotPos().y;

        if (x < minX)
            minX = x;

        if (y < minY)
            minY = y;
    }

    for (size_t i = 0; i < vSet.size(); i++) {

        Vertex * currVertex = vSet.at(i);

        double x = currVertex->getInfo().getPlotPos().x;
        double y = currVertex->getInfo().getPlotPos().y;
        int ID = currVertex->getInfo().getID();

        gv->addNode(currVertex->getInfo().getID(), x - minX, y - minY);
        gv->setVertexColor(currVertex->getInfo().getID(),currVertex->getInfo().getColor());

    }

    for (size_t i = 0; i < vSet.size(); i++) {


        for (size_t j = 0; j < vSet.at(i)->adj.size(); j++) {

            gv->addEdge(id, vSet.at(i)->adj.at(j).orig->info.getID(), vSet.at(i)->adj.at(j).dest->info.getID(), EdgeType::DIRECTED);

            int weight = (int)vSet.at(i)->adj.at(j).getWeight();
            gv->setEdgeWeight(id,weight);
            id++;
        }
    }

    gv->rearrange();
}
