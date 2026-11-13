#include <stdlib.h>

static void swap(int *x, int *y) { int t = *x; *x = *y; *y = t; }

static size_t partition(int *a, size_t lo, size_t hi) {
  swap(&a[lo + (size_t)rand() % (hi - lo)], &a[hi - 1]);
  size_t i = lo;
  for (size_t j = lo; j < hi - 1; j++)
    if (a[j] <= a[hi - 1]) swap(&a[i++], &a[j]);
  swap(&a[i], &a[hi - 1]);
  return i;
}

int randomizedSelect(int *a, size_t lo, size_t hi, size_t k) {
  for (;;) {
    if (lo + 1 == hi) return a[lo];
    size_t p = partition(a, lo, hi), rank = p - lo + 1;
    if (k == rank) return a[p];
    if (k < rank) hi = p;
    else { k -= rank; lo = p + 1; }
  }
}
