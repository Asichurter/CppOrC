#pragma once
class IntComparator {
public:
	static int compare(int e1, int e2) {
		return e1 - e2;
	}
};

class IntBoolComparator {
public:
	static bool compare(int e1, int e2) {
		return e1 >= e2;
	}
};