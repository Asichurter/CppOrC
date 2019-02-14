#pragma once
#include "InsertSort.h"

template <typename T> void swap(T a[], int l, int r) {
	T temp = a[l];
	a[l] = a[r];
	a[r] = temp;
}

//快速排序获得哨兵的位置：最左，最右，中间元素的中值
template <typename T, typename COMP> int getPivot(T a[], int l, int r) {
	int temp[3] = {l, r, (l+r)/2};
	if (COMP::compare(a[temp[0]], a[temp[1]]))
		swap<int>(temp, 0, 1);
	if (COMP::compare(a[temp[1]], a[temp[2]]))
		swap<int>(temp, 1, 2);
	if (COMP::compare(a[temp[0]], a[temp[1]]))
		swap<int>(temp, 0, 1);
	return temp[1];
}

//将序列以哨兵为界分割开
template <typename T, typename COMP> int seperate(T a[], int l, int r) {
	for (int r_ = r-1, l_ = l-1; l_ < r_; ) {
		while (++l_ < r_ && COMP::compare(a[r], a[l_]));
		while (r_ > l_ && COMP::compare(a[r_], a[r])) r_--;
		swap<T>(a, l_, r_);
		if (l_ == r_) return l_;
	}
}

//快速排序
template <typename T, typename COMP> void quickSort(T a[], int l, int r) {
	if (r <= l) return;
	if (r - l <= 2) {
		insertSort<T, COMP>(&a[l], r - l + 1, false);
		return;
	}
	int pivot = getPivot<T, COMP>(a, l, r);
	cout << "枢轴: " << a[pivot] << endl;
	//将哨兵移至最右侧保护起来
	swap<T>(a, pivot, r);
	int mid = seperate<T, COMP>(a, l, r);
	swap(a, r, mid);
	quickSort<T, COMP>(a, l, mid-1);
	quickSort<T, COMP>(a, mid + 1, r);
}
