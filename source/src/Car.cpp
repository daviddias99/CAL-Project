
#include "Car.h"
#include <queue>


Car::Car(uint carID, uint driverID, uint maxSeats, Person &driver)
{
	this->carID = carID;
	this->driverID = driverID;
	this->maxSeats = maxSeats;
	this->currentTakenSeats = 0;
	this->driver= driver;
}

uint Car::getCarID()
{
	return this->carID;
}

uint Car::getDriverID()
{
	return this->driverID;
}

uint Car::getMaxSeats()
{
	return this->maxSeats;
}

uint Car::getCurrentTakenSeats()
{
	return currentTakenSeats;
}

bool Car::isFull(){
    return maxSeats==(currentTakenSeats+1);
}
void makeEmpty(priority_queue<Vertex*> &q){
    while(!q.empty()){
        q.pop();
    }
}

double getDist(const Vertex &src, const Vertex &dest){
    for(auto e: src.getAdj()){
        if(e.getDest()->getInfo().getID()==dest.getInfo().getID())
            return e.getInfo().getDistance();
    }
    return 0;
}

void Car::fillCarGreedy(Graph &graph, unsigned &maxDist){
    priority_queue<Vertex*> q;
    unsigned dist= maxDist;
    unsigned currentVertex = driver.getSourceNodeID();
    unsigned dest= driver.getDestNodeID();
    Time currentTime = driver.getMinDepartureTime();
    Time maxArrivalTime = driver.getMaxArrivalTime();

    while (!isFull()){
        makeEmpty(q);
        for(auto v: graph.getVertexSet()){

        }
    }

}