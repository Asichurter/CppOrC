#pragma once
//检查序列是否有序
//reverse：序列的顺序
template <typename T, typename COMP> bool check(T a[], int num, bool reverse) {
	for (int i = 0; i < num - 1; i++) {
		if (!(reverse ? COMP::compare(a[i], a[i+1]) : COMP::compare(a[i+1], a[i])))
			return false;
	}
	return true;
}