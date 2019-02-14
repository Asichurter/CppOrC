#pragma once
#include <iostream>
#include "HfmTree.h"

template <typename T, typename COMP> class Heap {
private:
	T* Elements;
	int Size;
	int MaxSize;
	//�󶥶ѻ���С����
	bool MaxOrMin;

	bool siftDown(int pos) {
		//�����Ҷ�ڵ㣬�Ǿ�û��Ҫ���������ƶ��ˣ�����Ҫ���ϵݹ�
		if (Heap::isLeaf(pos))
			return true;
		else {
			//���û���ҽڵ㣬��ֻ�Ƚ���ڵ�
			if (Heap::right(pos) < 0) {
				if (compareByMaxOrMin(Elements[Heap::left(pos)], Elements[pos])) {
					swap(pos, Heap::left(pos));
					siftDown(Heap::left(pos));
					return true;
				}
				else return false;
				//�������ѣ�������ﷵ��...
			}
			else {
				//���ݴ󶥶ѻ���С���ѣ�ѡ����ֵ���siftDown�Ľڵ���н���
				//�����ֵ���siftDown�Ľڵ�ֵ���㽻���������Ǿͽ���
				//���һ���ڵ㲻��Ҷ�ڵ㣬��ô���ٿ϶�����ڵ�
				if (compareByMaxOrMin(Elements[Heap::left(pos)], Elements[Heap::right(pos)])) {
					if (compareByMaxOrMin(Elements[Heap::left(pos)], Elements[pos])) {
						swap(pos, Heap::left(pos));
						siftDown(Heap::left(pos));
						return true;
					}
					//���ڵ㲻���㽻�����������ڵ㲻��Ҫ�����ݹ���
					else return false;
				}
				//������ҽڵ㣬�ٶ��ҽڵ���еݹ�
				else {
					if (compareByMaxOrMin(Elements[Heap::right(pos)], Elements[pos])) {
						swap(pos, Heap::right(pos));
						siftDown(Heap::right(pos));
						return true;
					}
					//���ڵ㲻���㽻�����������ڵ㲻��Ҫ�����ݹ���
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
		//�ݹ鵽�˸��ڵ�
		if (Heap::parent(pos) < 0) {
			Heap::siftDown(pos);
		}
		else {
			if (siftDown(pos)) {
				Heap::insertHelper(Heap::parent(pos));
			}
			//����������ϵ�ĳ��siftdownû�иı䣬����Ҫ�����ϵݹ���
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
		//������ѭ��ʱ���ض�����0��λ�ã���ʱ����ҪsiftDown
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
			std::cout << "Ԫ�ظ�����������������ƣ�" << std::endl;
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
			//std::cout << "���ʸ��ڵ�ʱ��λ�ô���Ϊ0��" << std::endl;
			return -1;
		}
		return (pos - 1) / 2;
	}

	int left(int pos) {
		if (2 * pos + 1 >= Size) {
			//std::cout << Elements[pos] << " λ��û����ڵ㣡" << std::endl;
			return -1;
		}
		return 2 * pos + 1;
	}

	int right(int pos) {
		if (2 * pos + 2 >= Size) {
			//std::cout << Elements[pos] << " λ��û���ҽڵ㣡" << std::endl;
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
			std::cout << "���Դﵽ����������ƣ�" << std::endl;
		}
		else {
			Elements[Size] = ele;
			Size++;
			insertHelper(Size-1);
		}
	}

	void remove(T& ele) {
		if (Size == 0) {
			std::cout << "����û��Ԫ�أ�" << std::endl;
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
		//std::cout << "first��" << Elements[0] << std::endl;
		remove(Elements[0]);
		return Elements[Size];
	}

	T getPeak() {
		if (Size > 0)
			return Elements[0];
	}

	void printHeap() {
		if (Size == 0) {
			std::cout << "����û��Ԫ�أ�" << std::endl;
			return;
		}
		for (int i = 0; i < Size; i++) {
			std::cout << *(Elements + i) << std::endl;
		}
		std::cout << "Ԫ�ظ�����" << Size << std::endl;
	}
};
