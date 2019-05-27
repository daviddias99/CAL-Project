#include "Edge.h"


Edge::Edge(Vertex *o, Vertex *d, EdgeInfo w) : orig(o), dest(d), info(w) {}


double Edge::getWeight() const {
	return info.getTempo();
}

Vertex* Edge::getDest(){
    return this->dest;
}

EdgeInfo Edge::getInfo(){
    return this->info;
}