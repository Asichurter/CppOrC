#include <iostream>
#include "DoublyLinkedList.h"

using namespace std;

int main()
{
	DoublyLinkedList<int> list;
	list.insert(13);
	list.insert(29);
	list.insert(53);
	list.append(100);
	cout << "长度：" << list.length() << endl;
	list.showItems(true);
	cout << endl;
	list.next();
	list.remove();
	list.pre();
	list.remove();
	list.showItems(true);
	list.insert(66);
	list.insert(77);
	cout << endl;
	list.showItems(true);
	cout << "长度：" << list.length() << endl;
	list.moveToPos(0);
	cout << "第0个位置上的元素：" << list.get() << endl;
	
	int test = 66;
	cout << "是否含有元素66:" << list.hasEle(test) << endl;
	test = 78;
	cout << "是否含有元素78：" << list.hasEle(test) << endl;
	return 0;
}
