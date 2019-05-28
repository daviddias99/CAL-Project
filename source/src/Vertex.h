#pragma once

class Edge;
class Graph;
class GraphViewer;


#include "NodeInfo.h"

#include <vector>
#include "MutablePriorityQueue.h"
#include "EdgeInfo.h"
#include "Edge.h"

class Vertex {
	NodeInfo info;						// contents
	vector<Edge > adj;					// outgoing edges
	bool visited;						// auxiliary field
	double dist = 0;
	Vertex *path = nullptr;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	void addEdge(Vertex*dest, EdgeInfo w);


public:
	Vertex(NodeInfo in, int queueIndex = 0);
	bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue
	NodeInfo getInfo() const;
	NodeInfo& getInfoRef();
	int getQueueIndex();
	double getDist() const;
	Vertex *getPath() const;
	friend class Graph;
	friend class MutablePriorityQueue<Vertex>;
	friend void loadGraphForVis(GraphViewer* gv, Graph& graph);
	friend void showWholeMap();
	bool isVisited() const;
	vector<Edge> getAdj() const;
	void removePerson(Person person);
	bool fillGreedyComparable(Vertex & vertex) const;
};