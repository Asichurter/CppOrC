#pragma once
#ifndef HFMNODE_H
#define HFNODE_H

template <typename T> class HfmNode {
public:
	~HfmNode() {}
	virtual int weight() {
		return 0;
	}
	virtual bool isLeaf() {
		return true;
	}
	void clear() {}
};
#endif // !HFMNODE_H