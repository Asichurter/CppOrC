#pragma once
//#ifndef HFMNODE_H
//#define HFMNODE_H
#include "HfmNode.h"

template <typename T> class HfmLeafNode : public HfmNode<T>{
private:
	int Weight;
	T Letter;
public:
	HfmLeafNode(int w, T c) {
		Weight = w;
		Letter = c;
	}

	~HfmLeafNode() {}

	virtual int weight() {
		return Weight;
	}

	virtual bool isLeaf() {
		return true;
	}

	T& getChar() {
		return Letter;
	}

	void clear() {}
};
//#endif
