#include "Graph.h"

Graph::Graph(Vertice* ver, int vn, Edge* ed, int en) {
	for (int i = 0; i < vn; i++) {
		Graph::Vertices.append(ver[i]);
	}
	for (int i = 0; i < en; i++) {
		Edges.append(ed[i]);
	}
	Vertice_Num = vn;
}

//根据一个的名称，在图G中找到对应的节点指针
Vertice* Graph::findVertice(string name) {
	for (Graph::Vertices.moveToStart(); Graph::Vertices.hasNext(); Graph::Vertices.next()) {
		if (Graph::Vertices.get().Name == name)
			return &(Graph::Vertices.get());
	}
	throw "没有找到指定的地点！检查名称的合法性！";
}

//初始化dist数组：
void Graph::init_distances(map<Vertice*, int>& dist, map<Vertice*, string>& path, Vertice* start) {
	for (Vertices.moveToStart(); Vertices.hasNext(); Vertices.next()) {
		Vertice& vertice = Vertices.get();
		//只对除起始点以外的点进行操作
		if (vertice.Num != start->Num) {
			Edge* edge = start->adjacant(&(vertice));
			if (edge != NULL) {
				dist[&(vertice)] = edge->Weight;
				path[&(vertice)] = edge->End->Name;
			}
			else {
				dist[&(vertice)] = INFINITE;
				path[&(vertice)] = "";
			}
		}
	}
}

Vertice* Graph::findMin(map<Vertice*, int> all_dis) {
	int min = INFINITE;
	Vertice* min_ptr = NULL;
	map<Vertice*, int>::iterator it;
	for (it = all_dis.begin(); it != all_dis.end(); it++) {
		if (it->second < min) {
			min = it->second;
			min_ptr = it->first;
		}
	}
	return min_ptr;
}

void Graph::buildDistances(string start, map<Vertice*, int>& all_distances, map<Vertice*, string>& all_paths)
{
	try{
		Vertice* s = findVertice(start);
	}
	catch (const char* msg) {
		std::cout << msg << std::endl;
		return;
	}
	//初始化dist权重矩阵
	init_distances(all_distances, all_paths, s);
	for (int i = 0; i < Vertice_Num - 1; i++) {
		//先找到本次循环中权重最小的dist节点
		Vertice* min = findMin(all_distances);
		map<Vertice*, int>::iterator it;
		for (it = all_distances.begin(); it != all_distances.end(); it++) {
			Edge* edge = min->adjacant(it->first);
			if (it->first != min && edge != NULL) {
				try {
					int ad_weight = edge->Weight;
					//如果发现起始节点到min节点的距离加上min节点到目标节点的距离小于起始节点直接到目标节点的长度
					if (it->second > all_distances[min] + ad_weight) {
						all_distances[it->first] = all_distances[min] + ad_weight;
						all_paths[it->first] = all_paths[min] + min->Name;
					}
				}
				catch(const char* msg){
					std::cout << msg << std::endl;
				}
			}
		}
	}
}

void Graph::findPath(string start, string end, int* length, string&path) {
	map<Vertice*,int> distances;
	map<Vertice*,string> paths;
	buildDistances(start, distances, paths);
	Vertice* e = findVertice(end);
	*length = distances[e];
	path = paths[e];
}

