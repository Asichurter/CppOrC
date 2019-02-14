#pragma once
#include "LinkedStack.h"
#include <iostream>

using namespace std;

LinkedStack<int>& stackInsertSort(LinkedStack<int>& src) {
	static LinkedStack<int> rst;
	LinkedStack<int> temp;
	while (src.length() > 0) {
		int top = src.pop();
		//�����ջĿǰΪ��
		if (rst.length() == 0)
			rst.push(top);
		else {
			//ֻҪĿǰ��ֵ�Ƚ��ջ��С���ǾͰѽ��ջ���͵�temp��
			while (top < rst.topValue() && rst.length() > 0) {
				temp.push(rst.pop());
			}
			//������topֵ���뵽���ջ�ĺ���λ����
			rst.push(top);
			//�ٽ�topֵ֮�ϵ�Ԫ�ػ�ѹ��ջ��
			while (temp.length() > 0) {
				rst.push(temp.pop());
			}
		}
	}
	//�����������Դջ
	while (rst.length() > 0)
		src.push(rst.pop());
	return src;
}