
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
#define MAP_FOLDER_PATH "../resources/mapas/"
#define EDGE_FILE_PATH "/T01_edges_"
#define NODE_XY_FILE_PATH "/T01_nodes_X_Y_"
#define NODE_LL_FILE_PATH "/T01_nodes_lat_lon_"


#include "NodeInfo.h"
#include "Vertex.h"


class Graph {
	vector<Vertex*> vertexSet;    // vertex set
	string cidade;

	Vertex * initSingleSource(const NodeInfo &orig);
	bool relax(Vertex *v, Vertex *w, double weight);
	int ** W = nullptr;   // dist
	int **P = nullptr;   // path
	int findVertexIdx(const NodeInfo &in) const;
	void dfsVisit(Vertex *v, vector<NodeInfo> & res) const;
public:
	Vertex *findVertex(const NodeInfo &in) const;
	bool addVertex(const NodeInfo &in, int queueIndex = 0);
	bool addEdge(const NodeInfo &sourc, const NodeInfo &dest, EdgeInfo w);
	int getNumVertex() const;
	vector<Vertex *> getVertexSet() const;
	vector<NodeInfo> dfs(NodeInfo v) const;

	//single source
	void dijkstraShortestPath(const NodeInfo &s);
	void unweightedShortestPath(const NodeInfo &s);
	void bellmanFordShortestPath(const NodeInfo &s);
	vector<NodeInfo> getPath(const NodeInfo &origin, const NodeInfo &dest) const;
	int ** getWMatrix();

	//all pairs
	void floydWarshallShortestPath();
	vector<NodeInfo> getfloydWarshallPath(const NodeInfo &origin, const NodeInfo &dest) const;
	~Graph();

    /**************** Algorithm Functions  ***************/

    // Load a given city map into the graph
    void loadFromFile(string cidade);

    // Load people from the chosen city into the graph
    void loadPeople();
    void loadPeople(int linesToIgnore, int lines);

    // Builds the graph thats achievable from the chosen node. A dfs must always be executed before this function
    void buildAchievableGraph(Graph& newGraph);

    // Applies FW Algorithm and removeInvalidPeople in order to build the simplified graph composed of only people and
    // the drivers destination.
    void processGraph(Graph &newGraph,Person driver);

    // Removes people with time-incompatibiliteis with the driver
    void removeInvalidPeople(Person driver);

    // Uses the FW matrix to find the path of nodes that must be followed in order to take all the people of vector "persons"
    vector<NodeInfo> getPath(vector<Person> persons);

    /**************** Debugging Functions  ***************/
    void printDests();
    void printMatrices();


};







#endif /* GRAPH_H_ */
