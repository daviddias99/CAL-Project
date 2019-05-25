#pragma once

class Edge;
class Graph;
class GraphViewer;



#include <vector>

class Car {

	uint carID;
	uint driverID;
	uint maxSeats;
	uint currentTakenSeats;
	Person driver;
	vector<Person> passengers;


public:
	Car(uint carID,uint driverID, uint maxSeats);

	uint getCarID();
	uint getDriverID();
	uint getMaxSeats();
	uint getCurrentTakenSeats();
    bool isFull();
	void fillCarGreedy(Graph graph, unsigned maxDist);
};