#include <iostream>
#include "Graph.h"

int main() {
    
	Graph grafo;

	grafo.loadFromFile();
	grafo.floydWarshallShortestPath();


    return 0;
}