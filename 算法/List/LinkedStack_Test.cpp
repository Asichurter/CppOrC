#include <iostream>
#include "LinkedStack.h"

using namespace std;

int main()
{
	LinkedStack<int> stack;
	stack.push(5);
	stack.push(8);
	stack.push(2);
	stack.push(12);
	stack.push(18);
	stack.showAllItems();
	cout << endl;
	stack.pop();
	stack.pop();
	stack.push(21);
	stack.push(25);
	stack.showAllItems();
	cout << "³¤¶È£º" << stack.length() << endl;
	return 0;
}
