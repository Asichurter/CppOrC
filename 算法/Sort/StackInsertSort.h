#pragma once
#include "LinkedStack.h"
#include <iostream>

using namespace std;

LinkedStack<int>& stackInsertSort(LinkedStack<int>& src) {
	static LinkedStack<int> rst;
	LinkedStack<int> temp;
	while (src.length() > 0) {
		int top = src.pop();
		//若结果栈目前为空
		if (rst.length() == 0)
			rst.push(top);
		else {
			//只要目前的值比结果栈顶小，那就把结果栈顶送到temp中
			while (top < rst.topValue() && rst.length() > 0) {
				temp.push(rst.pop());
			}
			//结束后，top值插入到结果栈的合适位置上
			rst.push(top);
			//再将top值之上的元素回压至栈顶
			while (temp.length() > 0) {
				rst.push(temp.pop());
			}
		}
	}
	//将排序结果填回源栈
	while (rst.length() > 0)
		src.push(rst.pop());
	return src;
}