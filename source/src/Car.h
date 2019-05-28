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
	//vector<Person> passengers;


public:
	Car(uint carID, uint maxSeats, Person driver);

	uint getCarID();
	uint getDriverID();
	uint getMaxSeats();
	uint getCurrentTakenSeats();
    bool isFull();
    vector<Person> fillCarGreedy(Graph *graph, unsigned maxDist);
    //vector<Person> getPassengers();
};

double priorityFunction(Vertex *subjectVertex);



struct CustomCompare
{
    bool operator()(Vertex* lhs, Vertex* rhs)
    {
        return priorityFunction(lhs) > priorityFunction(rhs);
    }
};

#endif