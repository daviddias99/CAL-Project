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

double NodeInfo::realDistanceTo(NodeInfo node) const {

    double distance;
    const double EARTH_RADIUS = 6357500;

    coordinates_t coords1 = this->map_coords;
    coordinates_t coords2 = node.map_coords;

    distance = 2 * EARTH_RADIUS * asin(sqrt(pow(sin((coords1.latitude - coords2.latitude)/2),2) + cos(coords1.latitude)*cos(coords2.latitude)*pow(sin((coords1.longitude - coords2.longitude)/2),2)));

    return distance;
}

double NodeInfo::plotDistanceTo(NodeInfo node) const {

    plotPos_t coords1 = this->plot_coords;
    plotPos_t coords2 = node.plot_coords;

    return sqrt( (coords1.x - coords2.x) * (coords1.x - coords2.x) + (coords1.y - coords2.y) * (coords1.y - coords2.y));
}

string NodeInfo::getColor() const {

    switch(this->persons.size()){

        case 0:
            return "BLUE";
        case 1:
            return "CYAN";
        case 2:
            return "YELLOW";
        case 3:
            return "ORANGE";
        default:
            return "RED";

    }
}
