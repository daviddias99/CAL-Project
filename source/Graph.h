
/*
* Graph.h
*/
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <limits>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_set>
#include "MutablePriorityQueue.h"

using namespace std;

class Edge;
class Vertex;

#define INF 2147483647

#include "NodeInfo.h"
#include "Vertex.h"


class Graph {
	vector<Vertex*> vertexSet;    // vertex set

	Vertex * initSingleSource(const NodeInfo &orig);
	bool relax(Vertex *v, Vertex *w, double weight);
	int ** W = nullptr;   // dist
	int **P = nullptr;   // path
	int findVertexIdx(const NodeInfo &in) const;


public:
	Vertex *findVertex(const NodeInfo &in) const;
	bool addVertex(const NodeInfo &in);
	bool addEdge(const NodeInfo &sourc, const NodeInfo &dest, EdgeInfo w);
	int getNumVertex() const;
	vector<Vertex *> getVertexSet() const;

	//single source
	void dijkstraShortestPath(const NodeInfo &s);
	void unweightedShortestPath(const NodeInfo &s);
	void bellmanFordShortestPath(const NodeInfo &s);
	vector<NodeInfo> getPath(const NodeInfo &origin, const NodeInfo &dest) const;

	//all pairs
	void floydWarshallShortestPath();
	vector<NodeInfo> getfloydWarshallPath(const NodeInfo &origin, const NodeInfo &dest) const;
	~Graph();

	void loadFromFile();

};







#endif /* GRAPH_H_ */
