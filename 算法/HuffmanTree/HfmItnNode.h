#pragma once
//#ifndef HFMITNNODE_H
//#define HFMITNNODE_H
#include "HfmNode.h"

template <typename T> class HfmItnNode : public HfmNode<T>{
private:
	int Weight;
	HfmNode<T>* Left;
	HfmNode<T>* Right;
public:
	HfmItnNode(HfmNode<T>* l, HfmNode<T>* r) {
		Left = l;
		Right = r;
		Weight = l->weight() + r->weight();
	}

	~HfmItnNode() {}

	virtual int weight() {
		return Weight;
	}

	virtual bool isLeaf() {
		return false;
	}

	HfmNode<T>* left() {
		return Left;
	}

	HfmNode<T>* right() {
		return Right;
	}

	void clear() {
		Left->clear();
		Right->clear();
		delete Left;
		delete Right;
	}
};
//#endif