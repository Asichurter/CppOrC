#pragma once

template <typename T, typename COMP> class CountSortList {
private:
	int Num;
	T* Array;
	//用于标志是否该位置上有值
	bool* Tag;

	bool check(int start, int end, int skip, T& susp) {
		if (end >= start && start >= 0 && end < Num) {
			for (int i = start; i <= end; i++) {
                //只比较有值的位置
                //不跟自己比较
				if (i == skip || Tag[i] == false)
					continue;
				if (COMP::compare(susp, *(Array + i)) == 0)
					return false;
			}
			return true;
		}
		else return false;
	}

public:
	CountSortList(int num) {
		Num = num;
		Array = new T[Num];
		Tag = new bool[Num];
		for (int i = 0; i < Num; i++){
            *(Tag+i) = false;
		}
	}
	~CountSortList() {
		delete [] Array;
		delete [] Tag;
	}

	bool set(int pos, T ele) {
		if (pos >= 0 && pos < Num) {
			//一旦set，将对应位置上的tag置为true
			if (check(0, Num - 1, pos, ele)) {
				*(Array + pos) = ele;
				Tag[pos] = true;
				return true;
			}
		}
		return false;
	}

	int length() {
		return Num;
	}

	//只有对应位置上的tag为true时，get才有效
	T get(int pos) {
		if (pos >= 0 && pos < Num && Tag[pos])
			return *(Array + pos);
        else return NULL;
	}

    //寻找小于某个下标的元素值的个数
	int lessThan(int pos) {
		if (pos < 0 || pos >= Num)
			return -1;
		int count = 0;
		for (int i = 0; i < Num; i++) {
			if (COMP::compare(*(Array + i), *(Array + pos)) < 0)
				count++;
		}
		return count;
	}

	void show() {
		for (int i = 0; i < Num; i++) {
            if (Tag[i])
                std::cout << *(Array + i) << " ";
            else std::cout << "? ";
		}
		std::cout << std::endl;
	}
};

template <typename T, typename COMP> CountSortList<T, COMP> countSort(CountSortList<T, COMP> src) {
	CountSortList<T, COMP> sorted(src.length());
	for (int i = 0; i < src.length(); i++) {
		sorted.set(src.lessThan(i), src.get(i));
	}
	return sorted;
}
