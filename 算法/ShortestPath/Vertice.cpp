#include "Vertice.h"
#include "Edge.h"

Vertice::Vertice() {}

Vertice::Vertice(Edge** all, int num, string n) {
	for (int i = 0;i < num; i++){
		Vertice::All_Edges.append(all[i]);
	}
	Vertice::Name = n;
}

Edge* Vertice::adjacant(Vertice* ver) {
	for (Vertice::All_Edges.moveToStart(); Vertice::All_Edges.hasNext(); Vertice::All_Edges.next()) {
		if (All_Edges.get()->End->Num == ver->Num)
			return All_Edges.get();
	}
	return NULL;
}

int Vertice::getWeight(Vertice* tar) {
	for (All_Edges.moveToStart(); All_Edges.hasNext(); All_Edges.next()) {
		if (All_Edges.get()->End == tar)
			return All_Edges.get()->Weight;
	}
	throw "没有从指定的点的边集中找到符合条件的边！";
}