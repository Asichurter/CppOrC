#include "Decoder.h"
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

int main1(){

	string test;
	cin >> test;
	LinkedStack<Element> stack;
	if (!decode(stack, test)) {
		cout << "输入非法！" << endl;
	}
	while (stack.length() > 0) {
		Element ele = stack.pop();
		if (ele.isSym())
			cout << ele.getCh() << " ";
		else cout << ele.getVal() << " ";
	}
	cout << endl;
	/*
	LinkedStack<Element> test;
	test.push(Element(3));
	test.push(Element(4));
	test.push(Element('+', false));
	LinkedStack<Element> copy(test);
	cout << "源栈pop前：" << endl;
	test.showAllItems();
	test.pop();
	cout << "源栈：" << endl;
	test.showAllItems();
	cout << "复制栈：" << endl;
	copy.showAllItems();
	*/
	cin.get();
	cin.get();
    return 0;
}

double Cal(LinkedStack<Element> *stack)
{
	double sum = 0;
	LinkedStack<Element> temp;

	while (stack->length() != 0)
	{
		Element e = stack->pop();
		if (e.isSym())
		{
			if (e.getCh() == '+')
			{
				if (temp.length() < 2)
					throw 0;
				temp.push(Element(temp.pop().getVal() + temp.pop().getVal(), true));
			}
			else if (e.getCh() == '-')
			{
				if (temp.length() < 2)
					throw 0;
				temp.push(Element((temp.pop().getVal() - temp.pop().getVal())*-1, true));
			}
			else if (e.getCh() == '#')
			{
				if (temp.length() < 1)
					throw 0;
				temp.push(Element((temp.pop().getVal())*-1, true));
			}
			else if (e.getCh() == '*')
			{
				if (temp.length() < 2)
					throw 0;
				temp.push(Element(temp.pop().getVal()*temp.pop().getVal(), true));
			}
			else if (e.getCh() == '/')
			{
				if (temp.length() < 2)
					throw 0;
				double t1 = temp.pop().getVal();
				double t2 = temp.pop().getVal();
				if (t1 == 0)
					throw 2;
				temp.push(Element(t2 / t1, true));
			}
		}
		else
		{
			temp.push(e);
		}
	}
	sum = temp.pop().getVal();
	//cout << endl << sum<<endl;
	if (temp.length() != 0)
		throw 1;
	return sum;
}


double makeCalclute(string s) {
	//string test = "(#1.2+#3)*((#5+4)*#6)";
	LinkedStack<Element> stack;
	if (!decode(stack, s))
	{
		throw(3);
	}
	double ans;
	ans = Cal(&stack);

	return ans;
}


int main() {
	while (1){
	string test;
	cin >> test;
	try
	{
		cout << makeCalclute(test) << endl;
	}
	catch (int t)
	{
		if (t == 0)
			cout << "输入非法，符号多余！" << endl;
		if (t == 1)
			cout << "输入非法，数多余！" << endl;
		if (t == 2)
			cout << "输入非法，除0错误！" << endl;
		if (t == 3)
			cout << "输入非法，字符括号错误！" << endl;
	}
	cout << endl;
	system("pause");
	}
	return 0;
}
