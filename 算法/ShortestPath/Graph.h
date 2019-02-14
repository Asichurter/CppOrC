#pragma once
#include "Edge.h"
#include "Vertice.h"
#include <string>
#include <map>

class Graph {
private:
	LinkedList<Vertice> Vertices;
	LinkedList<Edge> Edges;
	Vertice* findVertice(string);
	void buildDistances(string,map<Vertice*, int>&,map<Vertice*, string>&);
	void init_distances(map<Vertice*, int>&, map<Vertice*, string>&, Vertice*);
	Vertice* findMin(map<Vertice*, int>);

public:
	Graph(Vertice* ver, int vn, Edge* ed, int en);
	int Vertice_Num;
	void findPath(string, string, int*, string&);
};