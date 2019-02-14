#include "StackInsertSort.h"
#include "SelectionSort.h"
#include "7.16.h"
#include "CountSortList.h"
#include "IntComparator.h"
#include "InsertSort.h"
#include "BubbleSort.h"
#include "HeapSort.h"
#include "ShellSort.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "SortChecker.h"
#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

int main()
{
	//栈的插入排序的测试代码
	/*
	LinkedStack<int> stack;
	for (int i = 0; i < 10; i++) {
		stack.push(rand() % 50);
	}
	stack.showAllItems();
	LinkedStack<int>& result = stackInsertSort(stack);
	result.showAllItems();
	*/
	//优化选择排序测试代码
	/*
	clock_t now, end;
	int a[100];
	now = clock();
	for (int time = 0; time < 10000; time++){

		for (int i = 0; i < 100; i++) {
			a[i] = rand() % 50;
		}
		selSort(a, 100);
	}
	end = clock();
	cout << "未优化的：" << end - now << endl;
	now = clock();
	for (int time = 0; time < 10000; time++) {
		for (int i = 0; i < 100; i++) {
			a[i] = rand() % 50;
		}
		selSortOpt(a, 100);
	}
	end = clock();
	cout << "优化的：" << end - now << endl;


	for (int t = 0; t < 18; t++){
		int a[5];
		for (int j = 0; j < 5; j++) {
			a[j] = rand() % 10;
		}
		sortFive(a);
		for (int i = 0; i < 5; i++) {
			cout << a[i] << " ";
		}
		cout << endl;
	}
	cout << endl;
	srand(243);
	CountSortList<int, IntComparator> list(10);
	for (int i = 0; i < 10; i++) {
		while (!list.set(i, rand() % 100));
	}
	cout << "排序前：" << endl;
	list.show();
	CountSortList<int, IntComparator> list_ = countSort(list);
	cout << "排序后：" << endl;
	list_.show();*/
	srand(time(NULL));
	int a[10];
	int b[10];
	for (int t = 0; t < 20; t++){
		for (int i = 0; i < 10; i++) {
			a[i] = rand() % 100;
			cout << a[i] << " ";
		}
		cout << endl;
		//insertSort<int, IntComparator>(a, 10, false);
		//bubbleSort<int, IntComparator>(a, 10, false);
		//heapSort<int, IntBoolComparator>(a, 10, false);
		//shellSort<int, IntBoolComparator>(a, 10, false);
		//mergeSort<int, IntBoolComparator>(a, b, 0, 9, false);
		quickSort<int, IntBoolComparator>(a, 0, 9);
		for (int j = 0; j < 10; j++) {
			cout << a[j] << " ";
		}
		cout << (check<int, IntBoolComparator>(a, 10, false) ? "Pass!" : "Fail!") << endl << endl;
	}
	cout << endl << "Done";
	cin.get();
	return 0;
}
