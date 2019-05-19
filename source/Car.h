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


public:
	Car(uint carID,uint driverID, uint maxSeats);

	uint getCarID();
	uint getDriverID();
	uint getMaxSeats();
	uint getCurrentTakenSeats();
};