#include "Vertex.h"


Vertex::Vertex(NodeInfo in) : info(in), visited(false) {}

/*
* Auxiliary function to add an outgoing edge to a vertex (this),
* with a given destination vertex (d) and edge weight (w).
*/

void Vertex::addEdge(Vertex *d, EdgeInfo w) {
	adj.push_back(Edge(this, d, w));
}


bool Vertex::operator<(Vertex & vertex) const {
	return this->dist < vertex.dist;
}


NodeInfo Vertex::getInfo() const {
	return this->info;
}


double Vertex::getDist() const {
	return this->dist;
}


Vertex *Vertex::getPath() const {
	return this->path;
}

NodeInfo &Vertex::getInfoRef()  {
    return this->info;
}

vector<Edge> Vertex::getAdj() const{
    return this->adj;
}

void Vertex::removePerson(Person person) {
    this->info.removePerson(person.getID());
}
