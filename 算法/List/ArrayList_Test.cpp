#include<iostream>
#include "ArrayList.h"

using namespace std;

int main()
{
	ArrayList<int> list;
	list.insert(6);
	list.append(1);
	list.insert(3);
	list.insert(7);
	list.insert(10);
	list.showAllItems();
	cout << "当前位置：" << list.curPos() << endl;
	cout << "长度：" << list.length() << endl;
	list.moveToPos(list.length()-2);
	cout << "倒数第二个位置元素：" << list.get() << endl;
	int test = 8;
	cout << "是否含有数字8：" << list.hasEle(test) << endl; 
	list.remove();
	list.showAllItems();
	return 0;
}
