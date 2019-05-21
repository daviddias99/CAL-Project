#include <iostream>
#include "VisLoader.h"
#include "PersonGen.h"



int main() {

	//Setup

	Graph grafo, simplifiedGraph;
	GraphViewer *gv = new GraphViewer(5000, 5000, false);

	gv->createWindow(1200, 1200);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");


    genPeople(5000,"Fafe");

	//Loading

	grafo.loadFromFile("Fafe");
	grafo.loadPeople();
	//Processing

	//Simplification number 1

	grafo.dfs(NodeInfo(1249745324));
	simplifiedGraph = grafo.buildAchievableGraph();
	loadGraphForVis(gv, simplifiedGraph);
	simplifiedGraph.floydWarshallShortestPath();
	simplifiedGraph.printMatrices();

    getchar();

	return 0;
}