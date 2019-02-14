#pragma once
#include "HfmTree.h"
#include "HfmComparator.h"
#include <iostream>
#include <string>
#include <map>

using namespace std;

//Ϊ�˱��ڽ��������������Ƚ������ַ�����Ƶ�ʽ�����һ��ֻ��һ���ڵ������ɭ��
//fre:Ƶ������ 
//ch:�ַ�����
//count:����
//���أ�����������ɭ��
template <typename T> HfmTree<T>** makeForest(int* fre, char* ch, int count) {
	HfmTree<T>** forest = new HfmTree<T>*[count];
	for (int i = 0; i < count; i++) {
		forest[i] = new HfmTree<T>(new HfmLeafNode<T>(fre[i], ch[i]), 1);
	}
	return forest;
}

//���ù���������ɭ�֣����������������������
//forest:����������ɭ��
//count:����
//���أ���������������ָ��
template <typename T> HfmTree<T>* buildHfmTree(HfmTree<T>** forest, int count) {
	Heap<HfmTree<T>*, HfmComparator> heap(forest, count, false, count);
	while (heap.heapSize() > 1) {
		HfmTree<T>* temp1 = heap.removeFirst();
		HfmTree<T>* temp2 = heap.removeFirst();
		//�ȳ�����Ԫ��СһЩ����Ϊ��С����
		HfmItnNode<T>* newRoot = new HfmItnNode<T>(temp1->root(), temp2->root());
		HfmTree<T>* newTree = new HfmTree<T>(newRoot, temp1->getNum()+temp2->getNum());
		//std::cout << "�ϳɺ������Ȩ�أ�" << newTree->root()->weight() << std::endl;
		heap.insert(newTree);
		delete temp1;
		delete temp2;
	}
	return heap.removeFirst();
}

//���ù��������������õĸ����ĵݹ��������������õ�ÿ���ַ��ı��벢��������ֵ�
//node:��ǰ�ݹ�Ĺ��������ڵ�
//code:��ǰ�ڵ�ı���ֵ
//table:���������ֵ�
void fillTable(HfmNode<char>* node, string code, map<char, string>& table) {
	if (node->isLeaf())
		table[((HfmLeafNode<char>*)node)->getChar()] = code;
	else {
		fillTable(((HfmItnNode<char>*)node)->left(), code + "0", table);
		fillTable(((HfmItnNode<char>*)node)->right(), code + "1", table);
	}
}

//���ù������������������ַ���Ӧ���ֵ�
//hfm:������������
//���أ��ַ��ı����ֵ�
map<char, string> makeTable(HfmTree<char>* hfm) {
	map<char, string> table;
	fillTable(hfm->root(), "", table);
	return table;
}

//�������е��ֵ䣬���ַ������й���������
//������
//src:ԭ�ַ���
//dit:���еĹ�����������ֵ�
//����:�������ַ���
string encode(string& src, map<char, string>& dit) {
	string res = "";
	for (int i = 0; i < src.length(); i++) {
		res += dit[src.at(i)];
	}
	return res;
}

//*******���ù����������������ַ�����ԭ*******
//����:
//src:�����ַ���
//hfm:�ñ����Ӧ�Ĺ�������
//����:ԭ�ַ���
string decode(string& src, HfmTree<char>* hfm) {
	string res = "";
	HfmNode<char>* curRoot = hfm->root();
	int index = 0;
	while (index <= src.length()) {
		if (curRoot->isLeaf()) {
			res += ((HfmLeafNode<char>*)curRoot)->getChar();
			curRoot = hfm->root();
			if (index == src.length())
				break;
		}
		else {
			if (index == src.length()) {
				return "";
			}
			if (src.at(index) == '1') {
				curRoot = ((HfmItnNode<char>*)curRoot)->right();
				index++;
			}
			else {
				curRoot = ((HfmItnNode<char>*)curRoot)->left();
				index++;
			}
		}
	}
	return res;
}

