
#include "Car.h"
#include "Graph.h"
#include <queue>
#define VELOCITY 833

Car::Car(uint carID, uint maxSeats, Person driver)
{
	this->carID = carID;
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
	return this->driver.getID();
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

double getDist(Vertex *src, Vertex *dest){
    for(auto e: src->getAdj()){
        if(e.getDest()->getInfo().getID()==dest->getInfo().getID())
            return e.getInfo().getDistance();
    }
    return INF;
}

double getTime(Vertex* src, Vertex* dest, const double &velocity){
    for(auto e: src->getAdj()){
        if(e.getDest()->getInfo().getID()==dest->getInfo().getID())
            return e.getInfo().getDistance()/velocity;
    }
    return INF;
}

Time addTime(Time t, double minutes){
    Time final;
    unsigned h= t.getHora();
    unsigned m= t.getMin();
    unsigned s= t.getSeg();
    h+=minutes/60;
    m+= (int)minutes%60;
    final=Time(h,m,s);
    return final;
}


void Car::fillCarGreedy(Graph &graph, unsigned &maxDist){
    priority_queue<Vertex*> q;
    unsigned dist= maxDist;
    Vertex* currentVertex =graph.findVertex(driver.getSourceNodeID());
    //unsigned dest= driver.getDestNodeID();
    Vertex* dest =graph.findVertex(driver.getDestNodeID());
    Time currentTime = driver.getMinDepartureTime();
    Time maxArrivalTime = driver.getMaxArrivalTime();
    Time supposeArrival;
    //candidateVertex candidate;
    //candidate.driverDest= dest;
    Vertex* u;
    while (!isFull()){
        makeEmpty(q);
        for(auto v: graph.getVertexSet()){
            if(getDist(currentVertex, v)<maxDist) {
                for (auto p:v->getInfo().getPeople()) {
                    //mandar queu
                }
            }
        }

        while(!q.empty()){
            u= q.top();
            q.pop();
            supposeArrival= addTime(currentTime, (getTime(currentVertex, u, VELOCITY)+getTime(u,dest,VELOCITY)));
        }
    }

}