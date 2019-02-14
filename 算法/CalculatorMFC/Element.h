#pragma once

class Element {
private:
	double Val;
	char Ch;
	bool isSymbol;
public:
	Element() {
		isSymbol = true;
	}
	Element(char sym) {
		isSymbol = true;
		Ch = sym;
	}
	Element(double val, bool tag) {
		isSymbol = false;
		Val = val;
	}

	/*
	Element(Element& src) {
		if (src.isSym()) {
			isSymbol = true;
			Ch = src.getCh();
		}
		else {
			isSymbol = false;
			Val = src.getVal();
		}
	}*/

	bool isSym() {
		return isSymbol;
	}

	double getVal() {
		return Val;
	}

	char getCh() {
		return Ch;
	}

	bool comparePrior(char ch) {
		if (Ch == '(')
			return false;
		if (ch == '+' || ch == '-') {
			if (Ch == '*' || Ch == '/')
				return true;
			else if (Ch == '-')
				return true;
		}
		else if (Ch == '/')
			return true;
		else return false;
	}
};