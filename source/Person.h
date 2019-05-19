//
// Created by david on 16-05-2019.
//

#ifndef PRO_PERSON_H
#define PRO_PERSON_H


#include "util.h"

class Person {

private:

    unsigned int ID;
    string name;
    Time minDepartureTime;
    Time maxArrivalTime;
    Time pickUpTime;

public:


    Person(unsigned int ID, string name);
    unsigned int getID();


};





#endif //PRO_PERSON_H
