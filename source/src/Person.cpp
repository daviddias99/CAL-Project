//
// Created by david on 16-05-2019.
//

#include "Person.h"

unsigned int Person::getID() {
    return this->ID;
}

Person::Person(unsigned int ID, string name) {

    this->ID = ID;
    this->name = name;

}

void Person::setTimes(Time minDep, Time maxArr) {

    this->minDepartureTime = minDep;
    this->maxArrivalTime = maxArr;

}

void Person::setNodes(unsigned int sourceID, unsigned int destID) {

    this->sourceNodeID = sourceID;
    this->destNodeID = destID;

}

