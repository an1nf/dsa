#include <stdlib.h>

size_t lis(const int *a, size_t n, int *out) {
  if (n == 0) return 0;
  size_t *len = malloc(n * sizeof *len), *prev = malloc(n * sizeof *prev);
  size_t best = 0;
  for (size_t i = 0; i < n; i++) {
    len[i] = 1;
    prev[i] = i;
    for (size_t j = 0; j < i; j++)
      if (a[j] <= a[i] && len[j] + 1 > len[i]) {
        len[i] = len[j] + 1;
        prev[i] = j;
      }
    if (len[i] > len[best]) best = i;
  }
  size_t k = len[best];
  for (size_t i = best, s = k; s > 0; i = prev[i]) out[--s] = a[i];
  free(len);
  free(prev);
  return k;
}
