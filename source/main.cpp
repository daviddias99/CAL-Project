#include <iostream>
#include "Graph.h"
#include "graph_viz/graphviewer.h"


void loadGraphForVis(GraphViewer* gv) {


	ifstream nodeFile, edgeFile;
	string currentLine;

	nodeFile.open("C:\\Users\\utilizador\\Documents\\Faculdade\\CAL-Project\\source\\mapas\\Fafe\\T01_nodes_X_Y_Fafe.txt");
	edgeFile.open("C:\\Users\\utilizador\\Documents\\Faculdade\\CAL-Project\\source\\mapas\\Fafe\\T01_edges_Fafe.txt");

	getline(nodeFile, currentLine);

	while (!nodeFile.eof()) {

		getline(nodeFile, currentLine);
		stringstream line(currentLine);

		char tempChar;
		unsigned int ID;
		coordinates_t coords;

		line >> tempChar >> ID >> tempChar >> coords.latitude >> tempChar >> coords.longitude;

		gv->addNode(ID, coords.latitude - 567213.5133103, coords.longitude - 4587664);
	}

	unsigned int ID = 0;
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


int main() {

	Graph grafo;

	GraphViewer *gv = new GraphViewer(50000, 50000, false);

	gv->createWindow(1200, 1200);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");
	loadGraphForVis(gv);


	grafo.loadFromFile();
	grafo.floydWarshallShortestPath();


	return 0;
}