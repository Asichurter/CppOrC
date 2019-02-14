#include <iostream>
#include "ArrayQueue.h"

using namespace std;

int main()
{
	ArrayQueue<int> queue;
	queue.enqueue(3);
	queue.enqueue(6);
	queue.enqueue(2);
	queue.enqueue(5);
	queue.showAllItems();
	queue.dequeue();
	queue.dequeue();
	queue.showAllItems();
	cout << queue.frontValue() << endl;
}
