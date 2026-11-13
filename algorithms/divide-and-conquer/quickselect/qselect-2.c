#include <stddef.h>

static void swap(int *x, int *y) { int t = *x; *x = *y; *y = t; }

static size_t partitionAround(int *a, size_t lo, size_t hi, int pivot) {
  for (size_t j = lo; j < hi; j++)
    if (a[j] == pivot) { swap(&a[j], &a[hi - 1]); break; }
  size_t i = lo;
  for (size_t j = lo; j < hi - 1; j++)
    if (a[j] <= pivot) swap(&a[i++], &a[j]);
  swap(&a[i], &a[hi - 1]);
  return i;
}

static void insertionSort(int *a, size_t lo, size_t hi) {
  for (size_t i = lo + 1; i < hi; i++)
    for (size_t j = i; j > lo && a[j - 1] > a[j]; j--) swap(&a[j], &a[j - 1]);
}

int deterministicSelect(int *a, size_t lo, size_t hi, size_t k) {
  for (;;) {
    size_t n = hi - lo;
    if (n <= 5) {
      insertionSort(a, lo, hi);
      return a[lo + k - 1];
    }
    size_t g = n / 5;
    for (size_t i = 0; i < g; i++) {
      insertionSort(a, lo + 5 * i, lo + 5 * i + 5);
      swap(&a[lo + i], &a[lo + 5 * i + 2]);
    }
    int pivot = deterministicSelect(a, lo, lo + g, (g + 1) / 2);
    size_t p = partitionAround(a, lo, hi, pivot), rank = p - lo + 1;
    if (k == rank) return a[p];
    if (k < rank) hi = p;
    else { k -= rank; lo = p + 1; }
  }
}
