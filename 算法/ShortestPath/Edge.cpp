#include "Edge.h"

Edge::Edge() {
	Start = NULL;
	End = NULL;
	Weight = INFINITE;
}

Edge::Edge(Vertice* s, Vertice* e, int w) {
	Edge::Start = s;
	Edge::End = e;
	Edge::Weight = w;
}