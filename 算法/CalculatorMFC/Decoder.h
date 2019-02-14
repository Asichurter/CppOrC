#include <string>
#include <cstdlib>
#include <iostream>
#include "Element.h"
#include "LinkedStack.h"

//判断一个字符是否是运算符号
bool isSymbol(char val) {
	return val == '+' || val == '-' || val == '*' || val == '/';
}

//判断一个字符是否是左右括号
bool isBracket(char ch) {
	return ch == '(' || ch == ')';
}

bool isDigitNum(char val) {
	return val >= 48 && val <= 57;
}

bool isLegalSymbol(char val) {
	return isSymbol(val) || isBracket(val) ||
		isDigitNum(val) || val == '#' || val == '.';
}

bool isDigits(char val) {
	return isDigitNum(val) || val == '.';
}

//将字符串转为逆波兰表示法表示的式子
//参数：src: 返回结果的栈，最终转换的逆波兰表达式将会储存在栈中
//      qua: 待转换的运算式字符串
bool decode(LinkedStack<Element>& src, string qua) {
	//值栈
	LinkedStack<Element> valStack;
	//符号栈
	LinkedStack<Element> symStack;
	for (unsigned int i = 0; i < qua.length(); i++) {
		if (!isLegalSymbol(qua.at(i)))
			return false;
		//如果某个字符是运算符
		if (isSymbol(qua.at(i))) {
			char ch = qua.at(i);
			const Element ele(ch);
			//如果符号栈为空，或者当前符号优先级更高，则直接压入符号栈
			if (symStack.length() == 0 || !symStack.topValue().comparePrior(ch))
				symStack.push(ele);
			//否则，当前符号栈不为空，且栈顶的符号优先级更高
			//则先将高优先级符号并入值栈，再压入低优先级符号
			else {
				//可能存在多个高优先级的栈顶
				//则将所有高优先级的栈顶移至值栈，再将当前的符号压入符号栈
				while (symStack.length() != 0 && symStack.topValue().comparePrior(ch)) {
					valStack.push(symStack.pop());
				}
				symStack.push(ele);
			}
		}
		//如果是左括号
		else if (qua.at(i) == '(') {
			symStack.push(Element(qua.at(i)));
		}
		//如果是右括号，需对符号栈退栈直到遇到左括号，将这些元素压入值栈
		else if (qua.at(i) == ')') {
			//std::cout << symStack.topValue().getCh() << std::endl;
			while (symStack.topValue().getCh() != '(') {
				//如果发现符号栈中元素弹完都没有发现左括号
				//这说明右括号比左括号多，输入非法
				if (symStack.length() == 0)
					return false;
				valStack.push(symStack.pop());
			}
			//排出左括号
			symStack.pop();
		}
		else {
			string number;
			//用于指示是否有#，如果有，需跳过一个位置
			bool skip = false;
			bool dot = false;
			//数字的长度，用于将i移动到下一个正确位置
			int increase = 0;
			if (qua.at(i) == '#') {
				if (i + 1 >= qua.length())
					return false;
				//用于处理#位于括号前的特殊情况
				if (qua.at(i + 1) == '(') {
					symStack.push(Element('#'));
					continue;
				}
				number.append("-");
				skip = true;
				increase++;
			}
			//如果有单目的符号，则会导致j向前多一位
			//读取一串数字，当运算式串读完，下一个字符不是数字或者小数点时，停止
			for (int j = (skip ? i + 1 : i); j < qua.length() && isDigits(qua.at(j)); j++) {
				char ch = qua.at(j);
				if (ch == '.') {
					if (dot)
						return false;
					else  dot = true;
				}
				if (!isLegalSymbol(ch))
					return false;
				increase++;
				number += ch;
			}
			//将读取到的数字字符串转换为double值，压入值栈
			valStack.push(Element(atof(number.c_str()), false));
			//将i向前置数字位数的个数
			i += increase - 1;
		}
	}
	//值栈是颠倒的，将其退栈再入结果栈才能得到正确答案
	while (symStack.length() > 0) {
		Element examiner = symStack.pop();
		//如果在最后符号栈中仍然有左括号
		//这说明左括号比右括号多，输入非法
		if (examiner.getCh() == '(')
			return false;
		valStack.push(examiner);
	}
	//将值栈的元素弹出到结果栈中
	while (valStack.length() > 0) {
		src.push(valStack.pop());
	}
	return true;
}












