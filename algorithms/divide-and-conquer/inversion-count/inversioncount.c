#include <stdlib.h>
#include <string.h>

static size_t mergeCount(int *a, size_t lo, size_t mid, size_t hi) {
  int *t = malloc((hi - lo) * sizeof *t);
  size_t l = lo, r = mid, s = 0, inv = 0;
  while (l < mid && r < hi) {
    if (a[l] <= a[r]) t[s++] = a[l++];
    else {
      t[s++] = a[r++];
      inv += mid - l;
    }
  }
  while (l < mid) t[s++] = a[l++];
  while (r < hi) t[s++] = a[r++];
  memcpy(a + lo, t, (hi - lo) * sizeof *t);
  free(t);
  return inv;
}

size_t countInversions(int *a, size_t lo, size_t hi) {
  if (lo + 1 >= hi) return 0;
  size_t mid = lo + (hi - lo) / 2;
  return countInversions(a, lo, mid) + countInversions(a, mid, hi) +
         mergeCount(a, lo, mid, hi);
}
