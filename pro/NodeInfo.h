//
// Created by david on 16-05-2019.
//

#ifndef PRO_NODEINFO_H
#define PRO_NODEINFO_H


#include "Person.h"
#include <vector>

using namespace std;

typedef struct coordinates {

    unsigned int latitude;
    unsigned int longitude;


}coordinates_t;


class NodeInfo {

private:



    vector<Person> persons;
    unsigned int ID;
    coordinates_t coords;

public:

    NodeInfo(unsigned int ID, coordinates_t coords);

    void addPerson(Person newPerson);
    void removePerson(unsigned int personID);
    unsigned int getID();
    coordinates_t getCoords();

};


#endif //PRO_NODEINFO_H
