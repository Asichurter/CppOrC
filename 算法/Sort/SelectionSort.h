#pragma once
template <typename T> void selSort(T A[] , int n) {
	for (int i = 0; i < n - 1; i++) {
		int index = i;
		for (int j = i; j < n; j++){
			if (A[j] < A[index]){
				index = j;
			}
		}
		T temp = A[i];
		A[i] = A[index];
		A[index] = temp;
	}
}

template <typename T> void selSortOpt(T A[], int n) {
	for (int i = 0; i < n - 1; i++) {
		int index = i;
		for (int j = i; j < n; j++) {
			if (A[j] < A[index]) {
				index = j;
			}
		}
		if (index != i) {
			T temp = A[i];
			A[i] = A[index];
			A[index] = temp;
		}
	}
}