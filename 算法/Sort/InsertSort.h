#pragma once
template <typename T, typename COMP> void insertSort(T a[], int num, bool reverse) {
	for (int i = 0; i < num; i++) {
		int j = i;
		while (j > 0 && (reverse ? COMP::compare(a[j], a[j-1]) : COMP::compare(a[j-1], a[j])) > 0) {
			T temp = a[j];
			a[j] = a[j - 1];
			a[j - 1] = temp;
			j--;
		}
	}
}

//������ϣ�������У���������Ĳ�������
//step:����
template <typename T, typename COMP> void insertSortByStep(T a[], int n, bool reverse, int step){
    //��һ�β�ѭ����step����
    for (int init = 0; init < (n >= step ? step: n); init++){
        //�ڶ���ѭ����ÿstep��Խ����
        for (int j = init; j < n; j+=step){
            if (j-step >= 0){
                int k = j;
                while (k > 0 && (reverse ? COMP::compare(a[k], a[k-step]) : COMP::compare(a[k-step], a[k]))){
                    T temp = a[k];
                    a[k] = a[k-step];
                    a[k-step] = temp;
                    k-=step;
                }
            }
        }
    }
}
