#pragma once
#include "InsertSort.h"

template <typename T, typename COMP> void shellSort(T a[], int n, bool reverse){
    for (int nn = n/2; nn >= 1; nn/=2){
        insertSortByStep<T, COMP>(a, n, reverse, nn);
    }
}

