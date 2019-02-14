#pragma once
#include "InsertSort.h"

template <typename T> void swap(T a[], int l, int r) {
	T temp = a[l];
	a[l] = a[r];
	a[r] = temp;
}

//�����������ڱ���λ�ã��������ң��м�Ԫ�ص���ֵ
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

//���������ڱ�Ϊ��ָ
template <typename T, typename COMP> int seperate(T a[], int l, int r) {
	for (int r_ = r-1, l_ = l-1; l_ < r_; ) {
		while (++l_ < r_ && COMP::compare(a[r], a[l_]));
		while (r_ > l_ && COMP::compare(a[r_], a[r])) r_--;
		swap<T>(a, l_, r_);
		if (l_ == r_) return l_;
	}
}

//��������
template <typename T, typename COMP> void quickSort(T a[], int l, int r) {
	if (r <= l) return;
	if (r - l <= 2) {
		insertSort<T, COMP>(&a[l], r - l + 1, false);
		return;
	}
	int pivot = getPivot<T, COMP>(a, l, r);
	cout << "����: " << a[pivot] << endl;
	//���ڱ��������Ҳౣ������
	swap<T>(a, pivot, r);
	int mid = seperate<T, COMP>(a, l, r);
	swap(a, r, mid);
	quickSort<T, COMP>(a, l, mid-1);
	quickSort<T, COMP>(a, mid + 1, r);
}
