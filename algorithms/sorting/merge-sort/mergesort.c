#include <stdlib.h>
#include <string.h>

static void merge(int *a, size_t lo, size_t mid, size_t hi) {
  int *t = malloc((hi - lo) * sizeof *t);
  size_t l = lo, r = mid, s = 0;
  while (l < mid && r < hi) t[s++] = a[l] <= a[r] ? a[l++] : a[r++];
  while (l < mid) t[s++] = a[l++];
  while (r < hi) t[s++] = a[r++];
  memcpy(a + lo, t, (hi - lo) * sizeof *t);
  free(t);
}

void mergeSort(int *a, size_t lo, size_t hi) {
  if (lo + 1 < hi) {
    size_t mid = lo + (hi - lo) / 2;
    mergeSort(a, lo, mid);
    mergeSort(a, mid, hi);
    merge(a, lo, mid, hi);
  }
}
