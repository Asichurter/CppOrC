#include "HashingFunction.h"
#include "LinkedHashing.h"
#include "IntComparator.h"
#include "AVL.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
	srand(time(NULL));
	/*
	LinkedHashing<int, int, HashingFunction> hash(10);
	for (int i = 0; i < 20; i++) {
		int r = rand() % 100;
		hash.insertHash(r, r);
	}
	hash.print();
	*/
	for (int j = 0; j < 100; j++){
		AVL<int, int, IntComparator> avl;
		for (int i = 0; i < 30; i++) {
			int r = rand() % 200;
			avl.insert(r, r);
		}
		avl.checkBalanced();
		avl.widthTraverse();
	}
	//avl.widthTraverse();
	cin.get();
	return 0;
}
