#include "Edge.h"


Edge::Edge(Vertex *o, Vertex *d, EdgeInfo w) : orig(o), dest(d), info(w) {}


double Edge::getWeight() const {
	return info.getTempo();
}

