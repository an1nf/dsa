#include <stdlib.h>

void countingSort(const int *a, int *out, size_t n, int k) {
  size_t *c = calloc((size_t)k + 1, sizeof *c);
  for (size_t i = 0; i < n; i++) c[a[i]]++;
  for (int i = 1; i <= k; i++) c[i] += c[i - 1];
  for (size_t i = n; i--; ) out[--c[a[i]]] = a[i];
  free(c);
}
