#include <iostream>
#include "ArrayStack.h"

using namespace std;

int main()
{
	ArrayStack<int> stack(20);
	stack.push(2);
	stack.push(1);
	stack.push(24);
	stack.push(16);
	stack.push(32);
	stack.pop();
	stack.pop();
	stack.push(66);
	//stack.showAllItems();
	while (stack.length() > 0){
		cout << stack.pop() << endl;
	}
	return 0;
}
