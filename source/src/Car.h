#ifndef CAR_H
#define CAR_H

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


public:
	Car(uint carID, uint maxSeats, Person driver);

	uint getCarID();
	uint getDriverID();
	uint getMaxSeats();
	uint getCurrentTakenSeats();
    bool isFull();
    vector<Person> fillCarGreedy(Graph *graph, unsigned maxDist);
};

double priorityFunction(Vertex *subjectVertex);





#endif