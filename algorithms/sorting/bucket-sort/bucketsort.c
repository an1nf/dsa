#include <stdlib.h>

void bucketSort(double *a, size_t n) {
  if (n == 0) return;
  double **b = malloc(n * sizeof *b);
  size_t *len = calloc(n, sizeof *len);
  for (size_t i = 0; i < n; i++) b[i] = malloc(n * sizeof **b);

  for (size_t i = 0; i < n; i++) {
    size_t k = (size_t)(n * a[i]);
    size_t j = len[k]++;
    for (; j > 0 && b[k][j - 1] > a[i]; j--)
      b[k][j] = b[k][j - 1];
    b[k][j] = a[i];
  }

  size_t s = 0;
  for (size_t k = 0; k < n; k++) {
    for (size_t j = 0; j < len[k]; j++) a[s++] = b[k][j];
    free(b[k]);
  }
  free(b);
  free(len);
}
