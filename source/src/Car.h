#pragma once

class Edge;
class Graph;
class GraphViewer;


#include <iostream>
#include <vector>
#include "Person.h"
#include "Vertex.h"

class Car {

	uint carID;
	uint maxSeats;
	uint currentTakenSeats;
	Person driver;
	vector<Person> passengers;


public:
	Car(uint carID, uint maxSeats, Person driver);

	uint getCarID();
	uint getDriverID();
	uint getMaxSeats();
	uint getCurrentTakenSeats();
    bool isFull();
    void fillCarGreedy(Graph &graph, unsigned &maxDist);
};

/*
struct candidateVertex{
    Vertex* src;
    Vertex* driverDest;
    Vertex* candidateDest;
    Vertex* candidate;
} candidateVertex;
 */