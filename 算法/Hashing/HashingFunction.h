#pragma once
class HashingFunction {
public:
	static int Hashing(int key, int num) {
		return key % num;
	}
};