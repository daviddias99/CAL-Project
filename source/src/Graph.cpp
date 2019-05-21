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

/*
* Performs a depth-first search (dfs) in a graph (this).
* Returns a vector with the contents of the vertices by dfs order.
* Follows the algorithm described in theoretical classes.
*/
vector<NodeInfo> Graph::dfs(NodeInfo v) const {
	vector<NodeInfo> res;
	for (auto v : vertexSet)
		v->visited = false;

	dfsVisit(findVertex(v), res);

	return res;
}

Graph Graph::getGraphAchievableFrom(Vertex * v) 
{
	vector<NodeInfo> res;
	dfsVisit(v, res);
	return this->buildAchievableGraph();
}

/*
* Auxiliary function that visits a vertex (v) and its adjacent, recursively.
* Updates a parameter with the list of visited node contents.
*/

void Graph::dfsVisit(Vertex *v, vector<NodeInfo> & res) const {
	v->visited = true;
	res.push_back(v->info);
	for (auto & e : v->adj) {
		auto w = e.dest;
		if (!w->visited)
			dfsVisit(w, res);
	}
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

int func(unsigned int vMax, double distance, unsigned int c) {

	return distance/vMax;
}

void Graph::loadFromFile(string cidade)
{
    this->cidade = cidade;
	ifstream nodeFile, edgeFile,plotFile;
	string currentLine,currentLine2, nodePathStr_XY, nodePathStr_LL, edgePathStr;

	ostringstream nodePath_XY;
	ostringstream nodePath_LL;
	ostringstream edgePath;


	nodePath_XY << MAP_FOLDER_PATH << cidade << NODE_XY_FILE_PATH << cidade << ".txt";
	nodePath_LL << MAP_FOLDER_PATH << cidade << NODE_LL_FILE_PATH << cidade << ".txt";
	edgePath << MAP_FOLDER_PATH << cidade << EDGE_FILE_PATH << cidade << ".txt";

	nodePathStr_XY = nodePath_XY.str();
	nodePathStr_LL = nodePath_LL.str();
	edgePathStr = edgePath.str();

	nodeFile.open(nodePathStr_LL);
	plotFile.open(nodePathStr_XY);
	edgeFile.open(edgePathStr);

	getline(nodeFile, currentLine);
	getline(plotFile, currentLine2);

	while (!nodeFile.eof()) {

		getline(nodeFile, currentLine);
		getline(plotFile, currentLine2);

		stringstream line(currentLine);
		stringstream line2(currentLine2);

		char tempChar;
		unsigned int ID;
		coordinates_t map_coords;
		plotPos_t plot_coords;

		line >> tempChar >> ID >> tempChar >> map_coords.latitude >> tempChar >> map_coords.longitude;
		line2 >> tempChar >> ID >> tempChar >> plot_coords.x >> tempChar >> plot_coords.y;

		NodeInfo info(ID, map_coords, plot_coords);

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

		Vertex* v1 = this->findVertex(NodeInfo(IDSource));
		Vertex* v2 = this->findVertex(NodeInfo(IDDest));

		this->addEdge(v1->getInfo(), v2->getInfo(), EdgeInfo(ID,833,v1->getInfo().realDistanceTo(v2->getInfo()),2,func));
		ID++;
	}

	return;
}

void Graph::printMatrices()
{
	ofstream wOutput;
	ofstream pOutput;

	wOutput.open("../resources/wFile.txt");
	pOutput.open("../resources/pFile.txt");

	for (int i = 0; i < vertexSet.size(); i++) {

		for (int j = 0; j < vertexSet.size(); j++) {

			if(W[i][j] == INF)
				wOutput << "INF" << '\t';
			else
				wOutput << W[i][j] << '\t';

		}

		wOutput << '\n';
	}



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

Graph Graph::buildAchievableGraph() {

	Graph newGraph;

	for (size_t i = 0; i < this->vertexSet.size(); i++) {

		if (vertexSet.at(i)->visited)
			newGraph.addVertex(vertexSet.at(i)->info);
	}

	for (size_t i = 0; i < this->vertexSet.size(); i++) {

		if (vertexSet.at(i)->visited) {

			for (size_t j = 0; j < vertexSet.at(i)->adj.size(); j++) {

				newGraph.addEdge(vertexSet.at(i)->adj.at(j).orig->info, vertexSet.at(i)->adj.at(j).dest->info, vertexSet.at(i)->adj.at(j).info);
			}

		}
			
	}

	return newGraph;
}

void Graph::loadPeople() {

    ifstream peopleFile;
    string currentLine,peopleFilePathStr;
    ostringstream peopleFilePath;

    peopleFilePath << "../resources/persons_" << cidade << ".txt";
    peopleFilePathStr = peopleFilePath.str();
    peopleFile.open(peopleFilePathStr);


    while (!peopleFile.eof()) {

        char tempChar;
        string name;
        Time time1, time2;
        unsigned int personID,hour,minute,nodeID1,nodeID2;

        getline(peopleFile, currentLine);
        stringstream line(currentLine);

        line >> tempChar >> personID >> tempChar >> name >> tempChar >> hour >> tempChar >> minute >> tempChar;
        time1 = Time(hour,minute);
        line >> hour >> tempChar >> minute >> tempChar;
        time2 = Time(hour,minute);
        line >> nodeID1 >> tempChar >> nodeID2;

        Person newPerson(personID,name);
        newPerson.setTimes(time1,time2);
        newPerson.setNodes(nodeID1,nodeID2);

        Vertex* startVertex = this->findVertex(NodeInfo(nodeID1));
        startVertex->getInfoRef().addPerson(newPerson);
    }

}
