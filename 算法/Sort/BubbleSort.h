#pragma once
#include <iostream>
template <typename T, typename COMP> void bubbleSort(T a[], int n, bool reverse) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = n - 1; j > i; j--) {
			if (reverse ? COMP::compare(a[j], a[j - 1]) > 0 : COMP::compare(a[j-1], a[j]) > 0) {
				T temp = a[j];
				a[j] = a[j - 1];
				a[j - 1] = temp;
			}
		}
	}
}