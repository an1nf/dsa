#include <stdlib.h>

void countingSort(const int *a, int *out, size_t n) {
  if (n == 0) return;
  int min = a[0], max = a[0];
  for (size_t i = 1; i < n; i++) {
    if (a[i] < min) min = a[i];
    if (a[i] > max) max = a[i];
  }
  size_t k = (size_t)(max - min) + 1;
  size_t *c = calloc(k, sizeof *c);
  for (size_t i = 0; i < n; i++) c[a[i] - min]++;
  for (size_t i = 1; i < k; i++) c[i] += c[i - 1];
  for (size_t i = n; i--; ) out[--c[a[i] - min]] = a[i];
  free(c);
}
