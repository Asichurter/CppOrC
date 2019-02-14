#pragma once

template <typename T, typename COMP> class CountSortList {
private:
	int Num;
	T* Array;
	//���ڱ�־�Ƿ��λ������ֵ
	bool* Tag;

	bool check(int start, int end, int skip, T& susp) {
		if (end >= start && start >= 0 && end < Num) {
			for (int i = start; i <= end; i++) {
                //ֻ�Ƚ���ֵ��λ��
                //�����Լ��Ƚ�
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
			//һ��set������Ӧλ���ϵ�tag��Ϊtrue
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

	//ֻ�ж�Ӧλ���ϵ�tagΪtrueʱ��get����Ч
	T get(int pos) {
		if (pos >= 0 && pos < Num && Tag[pos])
			return *(Array + pos);
        else return NULL;
	}

    //Ѱ��С��ĳ���±��Ԫ��ֵ�ĸ���
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
