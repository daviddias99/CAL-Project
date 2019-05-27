//
// Created by david on 16-05-2019.
//

#ifndef PRO_PERSON_H
#define PRO_PERSON_H


#include "util.h"

class Person {

private:

    int ID;
    string name;
    Time minDepartureTime;
    Time maxArrivalTime;
    Time pickUpTime;
    unsigned int sourceNodeID;
    unsigned int destNodeID;

public:


    Person(int ID = -1, string name = "DEFAULT");

    void setTimes(Time minDep,Time maxArr);
    void setNodes(unsigned int sourceID, unsigned int destID );
    unsigned int getID();
    unsigned int getDestNodeID();
    unsigned int getSourceNodeID();
    Time getMinDepartureTime();
    Time getMaxArrivalTime();

};





#endif //PRO_PERSON_H
