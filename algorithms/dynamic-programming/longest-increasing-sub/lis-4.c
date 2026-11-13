#include <stdlib.h>

size_t lis(const int *a, size_t n, int *out) {
  size_t *tail = malloc((n + 1) * sizeof *tail), *prev = malloc(n * sizeof *prev);
  size_t len = 0;
  for (size_t i = 0; i < n; i++) {
    size_t lo = 1, hi = len + 1;
    while (lo < hi) {
      size_t mid = lo + (hi - lo) / 2;
      if (a[tail[mid]] <= a[i]) lo = mid + 1;
      else hi = mid;
    }
    prev[i] = lo > 1 ? tail[lo - 1] : i;
    tail[lo] = i;
    if (lo > len) len = lo;
  }
  if (len > 0)
    for (size_t k = len, i = tail[len]; k > 0; i = prev[i]) out[--k] = a[i];
  free(tail);
  free(prev);
  return len;
}
