#pragma once
#include "HfmTree.h"
#include "HfmComparator.h"
#include <iostream>
#include <string>
#include <map>

using namespace std;

//为了便于建立哈夫曼树，先将所有字符及其频率建立成一个只有一个节点的树的森林
//fre:频率数组 
//ch:字符数组
//count:数量
//返回：哈夫曼树的森林
template <typename T> HfmTree<T>** makeForest(int* fre, char* ch, int count) {
	HfmTree<T>** forest = new HfmTree<T>*[count];
	for (int i = 0; i < count; i++) {
		forest[i] = new HfmTree<T>(new HfmLeafNode<T>(fre[i], ch[i]), 1);
	}
	return forest;
}

//利用哈夫曼树的森林，重整建立起哈夫曼编码树
//forest:哈夫曼树的森林
//count:数量
//返回：哈夫曼编码数的指针
template <typename T> HfmTree<T>* buildHfmTree(HfmTree<T>** forest, int count) {
	Heap<HfmTree<T>*, HfmComparator> heap(forest, count, false, count);
	while (heap.heapSize() > 1) {
		HfmTree<T>* temp1 = heap.removeFirst();
		HfmTree<T>* temp2 = heap.removeFirst();
		//先出来的元素小一些，因为是小顶堆
		HfmItnNode<T>* newRoot = new HfmItnNode<T>(temp1->root(), temp2->root());
		HfmTree<T>* newTree = new HfmTree<T>(newRoot, temp1->getNum()+temp2->getNum());
		//std::cout << "合成后的树的权重：" << newTree->root()->weight() << std::endl;
		heap.insert(newTree);
		delete temp1;
		delete temp2;
	}
	return heap.removeFirst();
}

//利用哈夫曼编码树调用的辅助的递归遍历方法，将会得到每个字符的编码并用于填充字典
//node:当前递归的哈夫曼树节点
//code:当前节点的编码值
//table:待填满的字典
void fillTable(HfmNode<char>* node, string code, map<char, string>& table) {
	if (node->isLeaf())
		table[((HfmLeafNode<char>*)node)->getChar()] = code;
	else {
		fillTable(((HfmItnNode<char>*)node)->left(), code + "0", table);
		fillTable(((HfmItnNode<char>*)node)->right(), code + "1", table);
	}
}

//利用哈夫曼编码数建立起字符对应的字典
//hfm:哈夫曼编码树
//返回：字符的编码字典
map<char, string> makeTable(HfmTree<char>* hfm) {
	map<char, string> table;
	fillTable(hfm->root(), "", table);
	return table;
}

//利用已有的字典，将字符串进行哈夫曼编码
//参数：
//src:原字符串
//dit:已有的哈夫曼编码的字典
//返回:编码后的字符串
string encode(string& src, map<char, string>& dit) {
	string res = "";
	for (int i = 0; i < src.length(); i++) {
		res += dit[src.at(i)];
	}
	return res;
}

//*******利用哈夫曼树，将编码字符串还原*******
//参数:
//src:编码字符串
//hfm:该编码对应的哈夫曼树
//返回:原字符串
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

