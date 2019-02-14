#pragma once
#include "LinkedList.h"
#include <string>

class Edge;

class Vertice {
private:
	LinkedList<Edge*> All_Edges;

public:
	Vertice();
	Vertice(Edge**,int,string);
	
	Edge* adjacant(Vertice*);
	int getWeight(Vertice*);
	Edge* getMinEdge();
	string Name;
	int Num;
};