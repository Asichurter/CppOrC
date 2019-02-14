#pragma once
void swap(int a[], int i, int j) {
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}
void sortThree(int a[]) {
	if (a[2] > a[1]) {
		if (a[0] > a[1]){
			swap(a, 0, 1);
			if (a[2] < a[1]) {
				swap(a, 1, 2);
			}
		}
	}
	else {
		if (a[0] > a[1]) {
			swap(a, 0, 2);
		}
		else {
			swap(a, 1, 2);
			if (a[0] > a[1]) {
				swap(a, 0, 1);
			}
		}
	}
}

void sortFiveAboveThree(int a[]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 2; j >= i; j--) {
			sortThree(&a[j]);
		}
	}
}

void sortFive(int a[]) {
	if (a[3] >= a[1]) {
		if (a[3] < a[2]){
			swap(a, 2, 3);
			if (a[4] >= a[2]) {
				if (a[4] < a[3])
					swap(a, 3, 4);
			}
			else {
				if (a[4] >= a[1]) {
					swap(a, 3, 4);
					swap(a, 2, 3);
				}
				else if (a[4] >= a[0]){
					for (int i = 4; i >= 2; i--) {
						swap(a, i, i - 1);
					}
				}
				else {
					for (int i = 4; i >= 1; i--) {
						swap(a, i, i - 1);
					}
				}
			}
		}
	}
}