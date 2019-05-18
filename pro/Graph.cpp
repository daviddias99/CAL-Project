#include "Graph.h"


int Graph::getNumVertex() const {
	return vertexSet.size();
}


vector<Vertex *> Graph::getVertexSet() const {
	return vertexSet;
}

/*
* Auxiliary function to find a vertex with a given content.
*/

Vertex * Graph::findVertex(const NodeInfo &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return nullptr;
}

/*
* Finds the index of the vertex with a given content.
*/

int Graph::findVertexIdx(const NodeInfo &in) const {
	for (unsigned i = 0; i < vertexSet.size(); i++)
		if (vertexSet[i]->info == in)
			return i;
	return -1;
}
/*
*  Adds a vertex with a given content or info (in) to a graph (this).
*  Returns true if successful, and false if a vertex with that content already exists.
*/

bool Graph::addVertex(const NodeInfo &in) {
	if (findVertex(in) != nullptr)
		return false;
	vertexSet.push_back(new Vertex(in));
	return true;
}

/*
* Adds an edge to a graph (this), given the contents of the source and
* destination vertices and the edge weight (w).
* Returns true if successful, and false if the source or destination vertex does not exist.
*/

bool Graph::addEdge(const NodeInfo &sourc, const NodeInfo &dest, EdgeInfo w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == nullptr || v2 == nullptr)
		return false;
	v1->addEdge(v2, w);
	return true;
}


/**************** Single Source Shortest Path algorithms ************/

/**
* Initializes single source shortest path data (path, dist).
* Receives the content of the source vertex and returns a pointer to the source vertex.
* Used by all single-source shortest path algorithms.
*/

Vertex * Graph::initSingleSource(const NodeInfo &origin) {
	for (auto v : vertexSet) {
		v->dist = INF;
		v->path = nullptr;
	}
	auto s = findVertex(origin);
	s->dist = 0;
	return s;
}

/**
* Analyzes an edge in single source shortest path algorithm.
* Returns true if the target vertex was relaxed (dist, path).
* Used by all single-source shortest path algorithms.
*/

inline bool Graph::relax(Vertex *v, Vertex *w, double weight) {
	if (v->dist + weight < w->dist) {
		w->dist = v->dist + weight;
		w->path = v;
		return true;
	}
	else
		return false;
}


void Graph::dijkstraShortestPath(const NodeInfo &origin) {
	auto s = initSingleSource(origin);
	MutablePriorityQueue<Vertex> q;
	q.insert(s);
	while (!q.empty()) {
		auto v = q.extractMin();
		for (auto e : v->adj) {
			auto oldDist = e.dest->dist;
			if (relax(v, e.dest, e.getWeight())) {
				if (oldDist == INF)
					q.insert(e.dest);
				else
					q.decreaseKey(e.dest);
			}
		}
	}
}


vector<NodeInfo> Graph::getPath(const NodeInfo &origin, const NodeInfo &dest) const {
	vector<NodeInfo> res;
	auto v = findVertex(dest);
	if (v == nullptr || v->dist == INF) // missing or disconnected
		return res;
	for (; v != nullptr; v = v->path)
		res.push_back(v->info);
	reverse(res.begin(), res.end());
	return res;
}


void Graph::unweightedShortestPath(const NodeInfo &orig) {
	auto s = initSingleSource(orig);
	queue< Vertex* > q;
	q.push(s);
	while (!q.empty()) {
		auto v = q.front();
		q.pop();
		for (auto e : v->adj)
			if (relax(v, e.dest, 1))
				q.push(e.dest);
	}
}


void Graph::bellmanFordShortestPath(const NodeInfo &orig) {
	initSingleSource(orig);
	for (unsigned i = 1; i < vertexSet.size(); i++)
		for (auto v : vertexSet)
			for (auto e : v->adj)
				relax(v, e.dest, e.getWeight());
	for (auto v : vertexSet)
		for (auto e : v->adj)
			if (relax(v, e.dest, e.getWeight()))
				cout << "Negative cycle!" << endl;
}


/**************** All Pairs Shortest Path  ***************/


void deleteMatrix(int **m, int n) {
	if (m != nullptr) {
		for (int i = 0; i < n; i++)
			if (m[i] != nullptr)
				delete[] m[i];
		delete[] m;
	}
}


Graph::~Graph() {
	deleteMatrix(W, vertexSet.size());
	deleteMatrix(P, vertexSet.size());
}

int func(unsigned int a, double b, unsigned int c) {

	return a + b + c;
}

void Graph::loadFromFile()
{
	ifstream nodeFile, edgeFile;
	string currentLine;

	nodeFile.open("T01_nodes_lat_lon_Fafe.txt");
	edgeFile.open("T01_edges_Fafe.txt");

	getline(nodeFile, currentLine);

	while (!nodeFile.eof()) {

		getline(nodeFile, currentLine);
		stringstream line(currentLine);

		char tempChar;
		unsigned int ID;
		coordinates_t coords;

		line >> tempChar >> ID >> tempChar >> coords.latitude >> tempChar >> coords.longitude;

		NodeInfo info(ID,coords);

		this->addVertex(info);
	}

	unsigned int ID = 0;
	getline(edgeFile, currentLine);

	while (!edgeFile.eof()) {

		getline(edgeFile, currentLine);
		stringstream line(currentLine);

		unsigned int IDSource,IDDest;
		char tempChar;

		line >> tempChar >> IDSource >> tempChar >> IDDest;

		this->addEdge(NodeInfo(IDSource), NodeInfo(IDDest), EdgeInfo(ID,50,150,2,func));
		ID++;
	}

	return;
}


void Graph::floydWarshallShortestPath() {
	unsigned n = vertexSet.size();
	deleteMatrix(W, n);
	deleteMatrix(P, n);
	W = new int *[n];
	P = new int *[n];
	for (unsigned i = 0; i < n; i++) {
		W[i] = new int[n];
		P[i] = new int[n];
		for (unsigned j = 0; j < n; j++) {
			W[i][j] = i == j ? 0 : INF;
			P[i][j] = -1;
		}
		for (auto e : vertexSet[i]->adj) {
			int j = findVertexIdx(e.dest->info);
			W[i][j] = e.getWeight();
			P[i][j] = i;
		}
	}

	for (unsigned k = 0; k < n; k++)
		for (unsigned i = 0; i < n; i++)
			for (unsigned j = 0; j < n; j++) {
				if (W[i][k] == INF || W[k][j] == INF)
					continue; // avoid overflow
				int val = W[i][k] + W[k][j];
				if (val < W[i][j]) {
					W[i][j] = val;
					P[i][j] = P[k][j];
				}
			}
}



vector<NodeInfo> Graph::getfloydWarshallPath(const NodeInfo &orig, const NodeInfo &dest) const {
	vector<NodeInfo> res;
	int i = findVertexIdx(orig);
	int j = findVertexIdx(dest);
	if (i == -1 || j == -1 || W[i][j] == INF) // missing or disconnected
		return res;
	for (; j != -1; j = P[i][j])
		res.push_back(vertexSet[j]->info);
	reverse(res.begin(), res.end());
	return res;
}
