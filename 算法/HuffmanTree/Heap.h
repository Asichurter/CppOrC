#pragma once
#include <iostream>
#include "HfmTree.h"

template <typename T, typename COMP> class Heap {
private:
	T* Elements;
	int Size;
	int MaxSize;
	//大顶堆还是小顶堆
	bool MaxOrMin;

	bool siftDown(int pos) {
		//如果是叶节点，那就没必要继续向下移动了，但是要向上递归
		if (Heap::isLeaf(pos))
			return true;
		else {
			//如果没有右节点，那只比较左节点
			if (Heap::right(pos) < 0) {
				if (compareByMaxOrMin(Elements[Heap::left(pos)], Elements[pos])) {
					swap(pos, Heap::left(pos));
					siftDown(Heap::left(pos));
					return true;
				}
				else return false;
				//如果满足堆，则从这里返回...
			}
			else {
				//根据大顶堆还是小顶堆，选择最值与待siftDown的节点进行交换
				//如果最值与待siftDown的节点值满足交换条件，那就交换
				//如果一个节点不是叶节点，那么至少肯定有左节点
				if (compareByMaxOrMin(Elements[Heap::left(pos)], Elements[Heap::right(pos)])) {
					if (compareByMaxOrMin(Elements[Heap::left(pos)], Elements[pos])) {
						swap(pos, Heap::left(pos));
						siftDown(Heap::left(pos));
						return true;
					}
					//父节点不满足交换条件，父节点不需要继续递归了
					else return false;
				}
				//如果有右节点，再对右节点进行递归
				else {
					if (compareByMaxOrMin(Elements[Heap::right(pos)], Elements[pos])) {
						swap(pos, Heap::right(pos));
						siftDown(Heap::right(pos));
						return true;
					}
					//父节点不满足交换条件，父节点不需要继续递归了
					else return false;
				}
			}
		}
	}

	void swap(int p1, int p2) {
		if (p1 >= Size || p2 >= Size)
			return;
		T temp = Elements[p1];
		Elements[p1] = Elements[p2];
		Elements[p2] = temp;
	}

	bool compareByMaxOrMin(T& e1, T& e2) {
		if (MaxOrMin) {
			return COMP::compare(e1, e2);
		}
		else return COMP::compare(e2, e1);
	}

	void insertHelper(int pos) {
		//递归到了根节点
		if (Heap::parent(pos) < 0) {
			Heap::siftDown(pos);
		}
		else {
			if (siftDown(pos)) {
				Heap::insertHelper(Heap::parent(pos));
			}
			//如果从下向上的某次siftdown没有改变，则不需要再向上递归了
		}
	}

	void buildHeap(int num) {
		for (int i = num / 2; i >= 0; i--) {
			siftDown(i);
		}
	}

	void removeHelper(int pos) {
		while (pos != 0) {
			siftDown(pos);
			pos = Heap::parent(pos);
		}
		//当跳出循环时，必定处于0的位置，此时还需要siftDown
		siftDown(0);
	}

	int findHelper(T& ele) {
		if (Size == 0)
			return -1;
		else {
			for (int i = 0; i < Size; i++) {
				if (Elements[i] == ele)
					return i;
			}
			return -1;
		}
	}

public:
	Heap(bool M = true, int Max = 30) {
		MaxSize = Max;
		Size = 0;
		MaxOrMin = M;
		Elements = new T[MaxSize];
	}

	Heap(T eles[], int num, bool M = true, int Max = 30) {
		if (num > Max) {
			std::cout << "元素个数大于最大数量限制！" << std::endl;
		}
		else {
			MaxSize = Max;
			Size = 0;
			MaxOrMin = M;
			Elements = new T[MaxSize];
			for (int i = 0; i < num; i++) {
				*(Elements + i) = eles[i];
			}
			Size += num;
			Heap::buildHeap(num);
		}
	}
	~Heap() {
		delete[] Elements;
	}

	int parent(int pos) {
		if (pos == 0) {
			//std::cout << "访问父节点时，位置代码为0！" << std::endl;
			return -1;
		}
		return (pos - 1) / 2;
	}

	int left(int pos) {
		if (2 * pos + 1 >= Size) {
			//std::cout << Elements[pos] << " 位置没有左节点！" << std::endl;
			return -1;
		}
		return 2 * pos + 1;
	}

	int right(int pos) {
		if (2 * pos + 2 >= Size) {
			//std::cout << Elements[pos] << " 位置没有右节点！" << std::endl;
			return -1;
		}
		return 2 * pos + 2;
	}

	bool isLeaf(int pos) {
		return pos >= Size / 2 && pos <= Size;
	}

	int heapSize() {
		return Size;
	}

	void insert(T& ele) {
		if (Size == MaxSize) {
			std::cout << "堆以达到最大数量限制！" << std::endl;
		}
		else {
			Elements[Size] = ele;
			Size++;
			insertHelper(Size-1);
		}
	}

	void remove(T& ele) {
		if (Size == 0) {
			std::cout << "堆中没有元素！" << std::endl;
			return;
		}
		int index = findHelper(ele);
		if (index == Size - 1) {
			Size--;
			return;
		}
		Heap::swap(Size - 1, index);
		Size--;
		removeHelper(index);
	}

	T& removeFirst() {
		//std::cout << "first：" << Elements[0] << std::endl;
		remove(Elements[0]);
		return Elements[Size];
	}

	T getPeak() {
		if (Size > 0)
			return Elements[0];
	}

	void printHeap() {
		if (Size == 0) {
			std::cout << "堆中没有元素！" << std::endl;
			return;
		}
		for (int i = 0; i < Size; i++) {
			std::cout << *(Elements + i) << std::endl;
		}
		std::cout << "元素个数：" << Size << std::endl;
	}
};
