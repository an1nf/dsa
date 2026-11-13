#include <stdlib.h>

static void swap(int *x, int *y) { int t = *x; *x = *y; *y = t; }

static size_t partition(int *a, size_t lo, size_t hi) {
  swap(&a[lo + (size_t)rand() % (hi - lo)], &a[hi - 1]);
  int pivot = a[hi - 1];
  size_t i = lo;
  for (size_t j = lo; j < hi - 1; j++)
    if (a[j] < pivot) swap(&a[i++], &a[j]);
  swap(&a[i], &a[hi - 1]);
  return i;
}

void randomizedQuickSort(int *a, size_t lo, size_t hi) {
  if (lo + 1 < hi) {
    size_t p = partition(a, lo, hi);
    randomizedQuickSort(a, lo, p);
    randomizedQuickSort(a, p + 1, hi);
  }
}
