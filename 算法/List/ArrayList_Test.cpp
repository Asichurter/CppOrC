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
	cout << "��ǰλ�ã�" << list.curPos() << endl;
	cout << "���ȣ�" << list.length() << endl;
	list.moveToPos(list.length()-2);
	cout << "�����ڶ���λ��Ԫ�أ�" << list.get() << endl;
	int test = 8;
	cout << "�Ƿ�������8��" << list.hasEle(test) << endl; 
	list.remove();
	list.showAllItems();
	return 0;
}
