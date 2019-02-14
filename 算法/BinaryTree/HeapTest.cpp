#include <iostream>
#include "Heap.h"
#include "IntComparator.h"

using namespace std;

int main2()
{
	
	int eles[] = {8, 29, 7, 56, 12, 11, 1};
	Heap<int, IntComparator> heap(eles, 7, false);
	heap.printHeap(); 
	int a = heap.removeFirst();
	cout << "第一个值：" << a << endl;
	heap.printHeap();
	cout << endl << endl;
	int ele = 33;
	heap.insert(ele);
	heap.printHeap();
	cout << endl << endl;
	heap.remove(ele);
	ele = 12;
	heap.remove(ele);
	ele = 56;
	heap.remove(ele);
	heap.printHeap();
	return 0; 
} 


