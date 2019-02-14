#pragma once
#include "Vertice.h"
#define INFINITE 1<<16

class Edge {
public:
	Vertice* Start;
	Vertice* End;
	int Weight;

	Edge();
	Edge(Vertice*, Vertice*, int);
};