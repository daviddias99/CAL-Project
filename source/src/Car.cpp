
#include "Car.h"
#include "Graph.h"
#include <queue>
#define VELOCITY 833

struct CustomCompare
{
    bool operator()(Vertex* lhs, Vertex* rhs)
    {
        return priorityFunction(lhs) > priorityFunction(rhs);
    }
};

struct candidateVertex {
    Vertex *current;
    Vertex *driverDest;
    Vertex *candidate;
    int **W;
};

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

double getTime(Vertex* src, Vertex* dest, const double &velocity){



    return infoStruct.W[src->getQueueIndex()][dest->getQueueIndex()];
}


double priorityFunction(Vertex *subjectVertex) {

    double currentToSubjectTime = infoStruct.W[infoStruct.current->getQueueIndex()][subjectVertex->getQueueIndex()];
    double subjectToDriverDestDistance = subjectVertex->getInfo().realDistanceTo(infoStruct.driverDest->getInfo());
    double subjectToDriverDestTime = infoStruct.W[subjectVertex->getQueueIndex()][infoStruct.driverDest->getQueueIndex()];


    return currentToSubjectTime*10 +subjectToDriverDestDistance/100 + subjectToDriverDestTime*10 ;
}



vector<Person> Car::fillCarGreedy(Graph *graph, unsigned maxDist){

    // NOTE: Vertex naming: the current vertex where the car is is called 'current', the candidate to the ride vertex is called 'U' and the destination vertex is called 'dest'.

    vector<Person> passengers;
    priority_queue<Vertex*,std::vector<Vertex*>,CustomCompare> q;

    driver.setPickupTime(driver.getMinDepartureTime());
    passengers.push_back(driver);
    currentTakenSeats=1;

    Vertex* u;
    Vertex* currentVertex = graph->findVertex(NodeInfo(driver.getSourceNodeID()));
    Vertex* dest = graph->findVertex(NodeInfo(driver.getDestNodeID()));

    Time currentTime = driver.getMinDepartureTime();
    Time maxArrivalTime = driver.getMaxArrivalTime();
    Time supposeArrival,uPersonMaxArrival,uPersonMinDeparture;

    Person uPerson;
    double timeUtoDest;
    double timeCurrentToU;


    infoStruct.driverDest = dest;
    infoStruct.W = graph->getWMatrix();

    while (!isFull()){

        makeEmpty(q);

        infoStruct.current = currentVertex;

        // add people to queue

        for(auto v: graph->getVertexSet()){

            double vDistance = currentVertex->getInfo().realDistanceTo(v->getInfo());

            if((int)!v->getInfo().getPeople().empty() && vDistance/1000 < maxDist) { //check if there's at least one person in vertex and if vertex is within searchable distance
                q.push(v);
            }
        }

        // check for best candidate

        while(!q.empty()){

            u= q.top();
            q.pop();

            uPerson= u->getInfo().getPeople()[0];
            uPersonMaxArrival=uPerson.getMaxArrivalTime();
            uPersonMinDeparture=uPerson.getMinDepartureTime();

            timeCurrentToU = getTime(currentVertex, u, VELOCITY);

            if(timeCurrentToU==INF) //if the candidate isn't reachable by the car
                continue;
            timeUtoDest =getTime(u,dest, VELOCITY);

            if(timeUtoDest==INF) //if the destination isn't reachable from the candidate
                continue;

            supposeArrival= currentTime + timeCurrentToU + timeUtoDest; // supposed time of arrivel with u added to the ride

            if(supposeArrival.passedToNext) // invalidade rides that cross to the next day
                continue;

            if(currentTime+ timeCurrentToU < uPersonMinDeparture ) // if the car would arrive before the minimum departure time
                continue;

            if (supposeArrival < maxArrivalTime && supposeArrival < uPersonMaxArrival){ // if the person is valid with the current ride setup and the ride is aceptable for the person

                currentTime= currentTime + timeCurrentToU; // update the current time
                uPerson.setPickupTime(currentTime);
                passengers.push_back(uPerson);
                u->removePerson(uPerson);
                currentTakenSeats+=1;
                u->removePerson(uPerson);
                currentVertex=u;

                if(uPersonMaxArrival< maxArrivalTime)
                    maxArrivalTime = uPersonMaxArrival;
                break; //this breaks to next lines carefull
            }

        }

        if (q.empty()){

            cout << "Empty queue - ArrivalTime: " << currentTime + getTime(graph->findVertex(NodeInfo(passengers.at(passengers.size()-1).getSourceNodeID())) ,dest, VELOCITY) << endl;
            return passengers;
        }

    }

    cout << "Full car - ArrivalTime: " << currentTime + getTime(graph->findVertex(NodeInfo(passengers.at(passengers.size()-1).getSourceNodeID())) ,dest, VELOCITY) << endl;
    return passengers;
}



