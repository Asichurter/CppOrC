
#include "Decoder.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

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
