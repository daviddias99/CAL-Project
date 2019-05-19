//
// Created by david on 16-05-2019.
//

#include "NodeInfo.h"

NodeInfo::NodeInfo(unsigned int ID, coordinates_t coords, plotPos_t plot) {

	this->map_coords = coords;
	this->plot_coords = plot;
	this->ID = ID;

}

NodeInfo::NodeInfo(unsigned int ID) {

	coordinates_t coords;
	coords.latitude = 0;
	coords.longitude = 0;
	this->map_coords = coords;
	this->ID = ID;

}

void NodeInfo::addPerson(Person newPerson) {

	persons.push_back(newPerson);

}

void NodeInfo::removePerson(unsigned int personID) {

	for (vector<Person>::iterator it = persons.begin(); it != persons.end(); it++) {

		if (it->getID() == personID) {

			persons.erase(it);
			break;
		}

	}
}

unsigned int NodeInfo::getID() {
	return ID;
}

coordinates_t NodeInfo::getCoords() {
	return map_coords;
}

plotPos_t NodeInfo::getPlotPos()
{
	return plot_coords;
}

bool NodeInfo::operator==(const NodeInfo& node) const {

	return this->ID == node.ID;
}
