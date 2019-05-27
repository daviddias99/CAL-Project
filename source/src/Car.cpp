
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




void Car::fillCarGreedy(Graph &graph, unsigned &maxDist){
    priority_queue<Vertex*> q;
    unsigned dist= maxDist;
    Vertex* currentVertex =graph.findVertex(driver.getSourceNodeID());
    Vertex* dest =graph.findVertex(driver.getDestNodeID());
    Time currentTime = driver.getMinDepartureTime();
    Time maxArrivalTime = driver.getMaxArrivalTime();
    Time supposeArrival;
    Time uPersonMaxArrival;
    double timeCurrentToU;
    Vertex* u;
    Person uPerson;


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
            uPerson= u->getInfo().getMinPerson();
            uPersonMaxArrival=uPerson.getMaxArrivalTime();
            q.pop();
            timeCurrentToU=getTime(currentVertex, u, VELOCITY);
            supposeArrival= currentTime + (timeCurrentToU+getTime(u,dest, VELOCITY));
            if (supposeArrival< maxArrivalTime && supposeArrival<uPersonMaxArrival){
                currentTime= currentTime+ timeCurrentToU;
                passengers.push_back(uPerson);
                u->removePerson(uPerson);
                currentVertex=u;

                if(uPersonMaxArrival< maxArrivalTime)
                    maxArrivalTime=uPersonMaxArrival;
                break;
            }

        }

        if (q.empty())
            return;
    }

}