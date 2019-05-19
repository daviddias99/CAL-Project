#pragma once

#include "EdgeInfo.h"


class Graph;
class Vertex;

class Edge {

	Vertex*orig; 	
	Vertex * dest;      // destination vertex
	EdgeInfo info;         // edge weight

	bool selected; // Fp07

public:
	Edge(Vertex *o, Vertex *d, EdgeInfo w);
	friend class Graph;
	friend class Vertex;

	// Fp07
	double getWeight() const;
};