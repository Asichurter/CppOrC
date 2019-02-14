#define HFMCOMPARATOR_H
#include "HfmTree.h"

class HfmComparator {
public:
	static bool compare(HfmTree<char>* r1, HfmTree<char>* r2) {
		return r1->root()->weight() >= r2->root()->weight();
	}
};
