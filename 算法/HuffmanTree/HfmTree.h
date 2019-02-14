#pragma once
#include <iostream>
#include "HfmItnNode.h"
#include "HfmLeafNode.h"
#include "Heap.h"
//#include "HfmComparator.h"
#include <string>

template <typename T> class HfmTree {
private:
	HfmNode<T>* Root;
	int DecodeNum;
public:
	HfmTree(HfmNode<T>* r, int num) {
		Root = r;
		DecodeNum = num;
	}

	~HfmTree() {}

	int getNum() {
		return DecodeNum;
	}

	HfmNode<T>* root() {
		return Root;
	}

	void traverse() {
		traverse(Root, "");
	}

	void traverse(HfmNode<T>* ro, std::string code) {
		//std::cout << code << std::endl;
		if (ro->isLeaf()) {
			std::cout << ((HfmLeafNode<T>*)ro)->getChar() << ", 编码:" << code << std::endl;
			return;
		}
		std::string l = code + "0";
		std::string r = code + "1";
		traverse(((HfmItnNode<T>*)ro)->left(), l);
		traverse(((HfmItnNode<T>*)ro)->right(), r);
	}

	void printLeafRoot() {
		if (Root->isLeaf()) {
			std::cout << "根节点字母：" << ((HfmLeafNode<T>*)Root)->getChar() << ",权重:" << ((HfmLeafNode<T>*)Root)->weight() << std::endl;
		}
	}
};
