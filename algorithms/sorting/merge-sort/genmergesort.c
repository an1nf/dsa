#include <stdlib.h>
#include <string.h>

typedef int (*Cmp)(const void *, const void *);

static void merge(char *a, size_t lo, size_t mid, size_t hi,
                  size_t sz, Cmp cmp) {
  char *t = malloc((hi - lo) * sz);
  size_t l = lo, r = mid, s = 0;
  while (l < mid && r < hi) {
    size_t k = cmp(a + l * sz, a + r * sz) <= 0 ? l++ : r++;
    memcpy(t + s++ * sz, a + k * sz, sz);
  }
  memcpy(t + s * sz, a + l * sz, (mid - l) * sz);
  s += mid - l;
  memcpy(t + s * sz, a + r * sz, (hi - r) * sz);
  memcpy(a + lo * sz, t, (hi - lo) * sz);
  free(t);
}

void mergeSort(void *a, size_t lo, size_t hi, size_t sz, Cmp cmp) {
  if (lo + 1 < hi) {
    size_t mid = lo + (hi - lo) / 2;
    mergeSort(a, lo, mid, sz, cmp);
    mergeSort(a, mid, hi, sz, cmp);
    merge(a, lo, mid, hi, sz, cmp);
  }
}
