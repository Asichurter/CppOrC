#include "Heap.h"
#include "IntComparator.h"
#include <iostream>

using namespace std;

int main1()
{
	int a[10] = { 12, 70, 33, 65, 24, 56, 48, 92, 86, 33 };
	Heap<int, IntComparator> heap(a, 10, true, 10);
	heap.printHeap();
	cin.get();
	return 0;
}