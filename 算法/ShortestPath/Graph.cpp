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

//����һ�������ƣ���ͼG���ҵ���Ӧ�Ľڵ�ָ��
Vertice* Graph::findVertice(string name) {
	for (Graph::Vertices.moveToStart(); Graph::Vertices.hasNext(); Graph::Vertices.next()) {
		if (Graph::Vertices.get().Name == name)
			return &(Graph::Vertices.get());
	}
	throw "û���ҵ�ָ���ĵص㣡������ƵĺϷ��ԣ�";
}

//��ʼ��dist���飺
void Graph::init_distances(map<Vertice*, int>& dist, map<Vertice*, string>& path, Vertice* start) {
	for (Vertices.moveToStart(); Vertices.hasNext(); Vertices.next()) {
		Vertice& vertice = Vertices.get();
		//ֻ�Գ���ʼ������ĵ���в���
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
	//��ʼ��distȨ�ؾ���
	init_distances(all_distances, all_paths, s);
	for (int i = 0; i < Vertice_Num - 1; i++) {
		//���ҵ�����ѭ����Ȩ����С��dist�ڵ�
		Vertice* min = findMin(all_distances);
		map<Vertice*, int>::iterator it;
		for (it = all_distances.begin(); it != all_distances.end(); it++) {
			Edge* edge = min->adjacant(it->first);
			if (it->first != min && edge != NULL) {
				try {
					int ad_weight = edge->Weight;
					//���������ʼ�ڵ㵽min�ڵ�ľ������min�ڵ㵽Ŀ��ڵ�ľ���С����ʼ�ڵ�ֱ�ӵ�Ŀ��ڵ�ĳ���
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

