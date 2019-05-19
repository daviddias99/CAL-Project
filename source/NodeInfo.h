//
// Created by david on 16-05-2019.
//

#ifndef PRO_NODEINFO_H
#define PRO_NODEINFO_H


#include "Person.h"
#include <vector>

using namespace std;

typedef struct coordinates {

    double latitude;
    double longitude;


}coordinates_t;

typedef struct plotPos {

	double x;
	double y;


}plotPos_t;


class NodeInfo {

private:

    vector<Person> persons;
    unsigned int ID;
    coordinates_t map_coords;
	plotPos_t plot_coords;

public:

    NodeInfo(unsigned int ID, coordinates_t coords, plotPos_t plot);
    NodeInfo(unsigned int ID);

    void addPerson(Person newPerson);
    void removePerson(unsigned int personID);
    unsigned int getID();
    coordinates_t getCoords();
	plotPos_t getPlotPos();
	bool operator==(const NodeInfo& node) const;
};


#endif //PRO_NODEINFO_H
