#include <iostream>
#include "BST.h"

using namespace std;

int main()
{
	BST<int> bst;
	int eles[16] = {18, 73, 10, 5, 68, 99, 27, 39, 41, 51, 32, 25, 4, 6, 98, 100};
	bst.insertMany(eles, 16);
	cout << endl << bst.widthTraverse() << endl;
	cout << bst.isBST(NULL, true) << endl;
	cin.get();
	return 0;
}
