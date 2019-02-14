#include <iostream> 
#include "LinkedList.h"

using namespace std;

int main()
{
	LinkedList<int> list;
	list.insert(21);
	list.insert(12);
	list.insert(18);
	list.insert(1);
	list.showAllItems();
	cout << list.length() << endl;
	cout << list.get() << endl;
	list.next();
	cout << list.get() << endl;
	int test = 12;
	if (list.hasEle(test)){
		cout << "КЌга" << test << endl << endl;
	}
	list.next();
	cout << list.remove() << endl << endl;;
	list.showAllItems();
	
	int test_2 = 5;
	list.append(test_2);
	list.showAllItems();
	
	list.pre();
	cout << list.get() << endl;
	list.next();
	cout << list.get() << endl;
	list.pre();
	cout << list.get() << endl;
	list.moveToStart();
	cout << list.get() << endl;
	
	list.clearLove();
	list.showAllItems();
	
	return 0;
}
