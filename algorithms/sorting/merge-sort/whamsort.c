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

static size_t runEnd(const int *a, size_t lo, size_t hi) {
  size_t i = lo + 1;
  while (i < hi && a[i - 1] <= a[i]) i++;
  return i;
}

void whamSort(int *a, size_t lo, size_t hi) {
  while (lo + 1 < hi) {
    size_t mid = runEnd(a, lo, hi);
    if (mid >= hi) return;
    size_t end = 2 * mid - lo < hi ? 2 * mid - lo : hi;
    whamSort(a, mid, end);
    merge(a, lo, mid, end);
  }
}
