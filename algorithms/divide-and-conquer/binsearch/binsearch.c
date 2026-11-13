#include <stddef.h>

size_t lowerBound(const int *a, size_t n, int key) {
  size_t lo = 0, hi = n;
  while (lo < hi) {
    size_t mid = lo + (hi - lo) / 2;
    if (a[mid] < key) lo = mid + 1;
    else hi = mid;
  }
  return lo;
}

int binarySearch(const int *a, size_t n, int key, size_t *pos) {
  size_t i = lowerBound(a, n, key);
  if (i < n && a[i] == key) {
    *pos = i;
    return 1;
  }
  return 0;
}
