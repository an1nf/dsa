#include <stdlib.h>
#include <string.h>

static void countingSortByDigit(int *a, int *tmp, size_t n, int exp) {
  size_t c[10] = {0};
  for (size_t i = 0; i < n; i++) c[a[i] / exp % 10]++;
  for (int d = 1; d < 10; d++) c[d] += c[d - 1];
  for (size_t i = n; i--; ) tmp[--c[a[i] / exp % 10]] = a[i];
  memcpy(a, tmp, n * sizeof *a);
}

void radixSort(int *a, size_t n) {
  if (n == 0) return;
  int max = a[0];
  for (size_t i = 1; i < n; i++)
    if (a[i] > max) max = a[i];
  int *tmp = malloc(n * sizeof *tmp);
  for (int exp = 1; max / exp > 0; exp *= 10)
    countingSortByDigit(a, tmp, n, exp);
  free(tmp);
}
