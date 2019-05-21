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

	//Loading

	grafo.loadFromFile("Fafe");
	grafo.loadPeople();
	//Processing

	//Simplification number 1

//	grafo.dfs(NodeInfo(1337026227));
//	simplifiedGraph = grafo.buildAchievableGraph();
//	Graph* grafo3 = simplifiedGraph.processGraph();
//    loadGraphForVis(gv, simplifiedGraph);
    loadGraphForVis(gv, grafo);

//	simplifiedGraph.floydWarshallShortestPath();
//	simplifiedGraph.printMatrices();

    getchar();

	return 0;
}