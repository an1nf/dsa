#include <stdint.h>
#include <stdlib.h>

static size_t lookupChain(size_t *m, const size_t *p, size_t n, size_t i, size_t j) {
  size_t *c = &m[i * (n + 1) + j];
  if (*c != SIZE_MAX) return *c;
  if (i == j) return *c = 0;
  for (size_t k = i; k < j; k++) {
    size_t q = lookupChain(m, p, n, i, k) + lookupChain(m, p, n, k + 1, j) +
               p[i - 1] * p[k] * p[j];
    if (q < *c) *c = q;
  }
  return *c;
}

size_t memoizedMatrixChain(const size_t *p, size_t n) {
  size_t *m = malloc((n + 1) * (n + 1) * sizeof *m);
  for (size_t i = 0; i < (n + 1) * (n + 1); i++) m[i] = SIZE_MAX;
  size_t cost = lookupChain(m, p, n, 1, n);
  free(m);
  return cost;
}
