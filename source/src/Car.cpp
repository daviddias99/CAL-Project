
#include "Car.h"
#include "Graph.h"
#include <queue>
#define VELOCITY 833

struct candidateVertex{
    Vertex* current;
    Vertex* driverDest;
    Vertex* candidate;
} candidateVertex_t;

struct candidateVertex infoStruct;

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

/*
vector<Person> Car::getPassengers(){
    return this->passengers;
}
*/
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

    return maxSeats==currentTakenSeats;

}
void makeEmpty(priority_queue<Vertex*,std::vector<Vertex*>,CustomCompare> &q){
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
        if(e.getDest()->getInfo().getID()==dest->getInfo().getID()){

            return e.getInfo().getTempo();
        }

    }
    return INF;
}


double priorityFunction(Vertex *subjectVertex) {

    double currentToSubjectDistance = infoStruct.current->getInfo().realDistanceTo(subjectVertex->getInfo());
    double subjectToDriverDestDistance = subjectVertex->getInfo().realDistanceTo(infoStruct.driverDest->getInfo());


    return currentToSubjectDistance +subjectToDriverDestDistance ;
}



vector<Person> Car::fillCarGreedy(Graph *graph, unsigned maxDist){
    vector<Person> passengers;
    passengers.push_back(driver);
    currentTakenSeats=1;
    priority_queue<Vertex*,std::vector<Vertex*>,CustomCompare> q;
    unsigned dist= maxDist;
    Vertex* currentVertex =graph->findVertex(NodeInfo(driver.getSourceNodeID()));
    Vertex* dest =graph->findVertex(NodeInfo(driver.getDestNodeID()));
    Time currentTime = driver.getMinDepartureTime();
    Time maxArrivalTime = driver.getMaxArrivalTime();
    Time supposeArrival;
    Time uPersonMaxArrival;
    Time uPersonMinDeparture;
    double timeCurrentToU;
    Vertex* u;
    Person uPerson;
    double timeUtoDest;

    infoStruct.driverDest = dest;


    while (!isFull()){
        makeEmpty(q);

        infoStruct.current = currentVertex;

        for(auto v: graph->getVertexSet()){
            if(v->getInfo().getPeople().size()!=0 && getDist(currentVertex, v)<maxDist) { //check if there's at least one person in vertex and if vertex is within searchable distance
                q.push(v);
            }
        }

        while(!q.empty()){
            u= q.top();
            uPerson= u->getInfo().getPeople()[0];

            uPersonMaxArrival=uPerson.getMaxArrivalTime();
            uPersonMinDeparture=uPerson.getMinDepartureTime();
            q.pop();

            if(currentTime < uPersonMinDeparture )
                continue;
            if(find(passengers.begin(), passengers.end(), uPerson) != passengers.end()) //check if person is in car
                continue;
            timeCurrentToU=getTime(currentVertex, u, VELOCITY);
            if(timeCurrentToU==INF)
                continue;
            timeUtoDest =getTime(u,dest, VELOCITY);
            if(timeUtoDest==INF)
                continue;
            supposeArrival= (currentTime + (timeCurrentToU+timeUtoDest));

            if (supposeArrival< maxArrivalTime && supposeArrival<uPersonMaxArrival){

                currentTime= currentTime+ timeCurrentToU;
                uPerson.setPickupTime(currentTime);
                passengers.push_back(uPerson);

                currentTakenSeats+=1;
                u->removePerson(uPerson);
                currentVertex=u;

                if(uPersonMaxArrival< maxArrivalTime)
                    maxArrivalTime=uPersonMaxArrival;
                break; //this breaks to next lines carefull
            }

        }

        if (q.empty())
            return passengers;
    }

    cout << "ArrivalTime: " << currentTime << endl;
    return passengers;
}



