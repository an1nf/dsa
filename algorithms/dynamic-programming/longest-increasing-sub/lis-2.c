#include <stdint.h>
#include <stdlib.h>

static size_t aux(const int *a, size_t n, size_t i, size_t b, size_t *memo) {
  size_t *m = &memo[i * (n + 1) + b];
  if (*m != SIZE_MAX) return *m;
  if (i == 0) return *m = 0;
  size_t best = aux(a, n, i - 1, b, memo);
  if (b == n || a[i - 1] <= a[b]) {
    size_t take = 1 + aux(a, n, i - 1, i - 1, memo);
    if (take > best) best = take;
  }
  return *m = best;
}

size_t memoizedLis(const int *a, size_t n, int *out) {
  size_t *memo = malloc((n + 1) * (n + 1) * sizeof *memo);
  for (size_t i = 0; i < (n + 1) * (n + 1); i++) memo[i] = SIZE_MAX;
  size_t len = aux(a, n, n, n, memo), k = len;
  for (size_t i = n, b = n; k > 0; i--)
    if (aux(a, n, i, b, memo) != aux(a, n, i - 1, b, memo)) {
      out[--k] = a[i - 1];
      b = i - 1;
    }
  free(memo);
  return len;
}
