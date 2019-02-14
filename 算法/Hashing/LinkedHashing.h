#pragma once
#include <iostream>
#include "Link.h"

using namespace std;

template <typename K, typename T, typename HF> class LinkedHashing {
public:
	Link<K, T>** Slots;
	int Num;

	LinkedHashing(int num) {
		Num = num;
		Slots = new Link<K, T>*[Num];
		for (int i = 0; i < Num; i++) {
			*(Slots + i) = NULL;
		}
	}

	void insertHash(K& key, T& ele) {
		int offset = HF::Hashing(key, Num);
		if (*(Slots + offset) == NULL) {
			*(Slots + offset) = new Link<K, T>(key, ele);
		}
		else {
			Link<K, T>* cur = *(Slots + offset);
			while (cur->Next != NULL)
				cur = cur->Next;
			cur->Next = new Link<K, T>(key, ele);
		}
	}

	void print() {
		for (int i = 0; i < Num; i++) {
			cout << "µÚ" << i << "¸öSlot:";
			if (*(Slots + i) == NULL) {
				cout << "¿Õ" << endl;
			}
			else {
				Link<K, T>* cur = *(Slots + i);
				while (cur != NULL) {
					cout << " (" << cur->Key << ", " << cur->Element << ") ";
					cur = cur->Next;
				}
				cout << endl;
			}
		}
	}
};