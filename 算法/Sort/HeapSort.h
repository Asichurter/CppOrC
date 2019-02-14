#pragma once
#include "Heap.h"

template <typename T, typename COMP> void heapSort(T a[], int num, bool reverse) {
	Heap<T, COMP> heap(a, num, reverse, num);
	for (int i = 0; i < num; i++) {
		a[i] = heap.removeFirst();
	}
}