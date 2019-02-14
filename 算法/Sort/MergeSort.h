template <typename T, typename COMP> void mergeSort(T a[], T b[], int l, int r, bool reverse){
	//在长度为1时，直接返回
    if (r-l == 0) return;
    mergeSort<T, COMP>(a, b, l, (l+r)/2, reverse);
    mergeSort<T, COMP>(a, b, (l+r)/2+1, r, reverse);
    //拷贝忍者
    for (int i = l; i <= (r+l)/2; i++){
        b[i] = a[i];
    }
	//将第二个有序序列反向拷贝到临时数组b的后部以便从反向遍历第二个有序序列
	for (int i = 0; i <= r - (r + l) / 2 - 1; i++) {
		b[r-i] = a[(r + l) / 2 + 1 + i];
	}
    for (int i=l, j=r, k=l; k <= r;){
		if (reverse ? COMP::compare(b[i], b[j]) : COMP::compare(b[j], b[i]))
			a[k++] = b[i++];
		else a[k++] = b[j--];
    }
}
