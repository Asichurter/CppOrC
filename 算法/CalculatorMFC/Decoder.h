#include <string>
#include <cstdlib>
#include <iostream>
#include "Element.h"
#include "LinkedStack.h"

//�ж�һ���ַ��Ƿ����������
bool isSymbol(char val) {
	return val == '+' || val == '-' || val == '*' || val == '/';
}

//�ж�һ���ַ��Ƿ�����������
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

//���ַ���תΪ�沨����ʾ����ʾ��ʽ��
//������src: ���ؽ����ջ������ת�����沨�����ʽ���ᴢ����ջ��
//      qua: ��ת��������ʽ�ַ���
bool decode(LinkedStack<Element>& src, string qua) {
	//ֵջ
	LinkedStack<Element> valStack;
	//����ջ
	LinkedStack<Element> symStack;
	for (unsigned int i = 0; i < qua.length(); i++) {
		if (!isLegalSymbol(qua.at(i)))
			return false;
		//���ĳ���ַ��������
		if (isSymbol(qua.at(i))) {
			char ch = qua.at(i);
			const Element ele(ch);
			//�������ջΪ�գ����ߵ�ǰ�������ȼ����ߣ���ֱ��ѹ�����ջ
			if (symStack.length() == 0 || !symStack.topValue().comparePrior(ch))
				symStack.push(ele);
			//���򣬵�ǰ����ջ��Ϊ�գ���ջ���ķ������ȼ�����
			//���Ƚ������ȼ����Ų���ֵջ����ѹ������ȼ�����
			else {
				//���ܴ��ڶ�������ȼ���ջ��
				//�����и����ȼ���ջ������ֵջ���ٽ���ǰ�ķ���ѹ�����ջ
				while (symStack.length() != 0 && symStack.topValue().comparePrior(ch)) {
					valStack.push(symStack.pop());
				}
				symStack.push(ele);
			}
		}
		//�����������
		else if (qua.at(i) == '(') {
			symStack.push(Element(qua.at(i)));
		}
		//����������ţ���Է���ջ��ջֱ�����������ţ�����ЩԪ��ѹ��ֵջ
		else if (qua.at(i) == ')') {
			//std::cout << symStack.topValue().getCh() << std::endl;
			while (symStack.topValue().getCh() != '(') {
				//������ַ���ջ��Ԫ�ص��궼û�з���������
				//��˵�������ű������Ŷ࣬����Ƿ�
				if (symStack.length() == 0)
					return false;
				valStack.push(symStack.pop());
			}
			//�ų�������
			symStack.pop();
		}
		else {
			string number;
			//����ָʾ�Ƿ���#������У�������һ��λ��
			bool skip = false;
			bool dot = false;
			//���ֵĳ��ȣ����ڽ�i�ƶ�����һ����ȷλ��
			int increase = 0;
			if (qua.at(i) == '#') {
				if (i + 1 >= qua.length())
					return false;
				//���ڴ���#λ������ǰ���������
				if (qua.at(i + 1) == '(') {
					symStack.push(Element('#'));
					continue;
				}
				number.append("-");
				skip = true;
				increase++;
			}
			//����е�Ŀ�ķ��ţ���ᵼ��j��ǰ��һλ
			//��ȡһ�����֣�������ʽ�����꣬��һ���ַ��������ֻ���С����ʱ��ֹͣ
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
			//����ȡ���������ַ���ת��Ϊdoubleֵ��ѹ��ֵջ
			valStack.push(Element(atof(number.c_str()), false));
			//��i��ǰ������λ���ĸ���
			i += increase - 1;
		}
	}
	//ֵջ�ǵߵ��ģ�������ջ������ջ���ܵõ���ȷ��
	while (symStack.length() > 0) {
		Element examiner = symStack.pop();
		//�����������ջ����Ȼ��������
		//��˵�������ű������Ŷ࣬����Ƿ�
		if (examiner.getCh() == '(')
			return false;
		valStack.push(examiner);
	}
	//��ֵջ��Ԫ�ص��������ջ��
	while (valStack.length() > 0) {
		src.push(valStack.pop());
	}
	return true;
}












