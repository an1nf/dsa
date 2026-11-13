#include <stddef.h>
#include <stdint.h>

size_t recursiveMatrixChain(const size_t *p, size_t i, size_t j) {
  if (i == j) return 0;
  size_t best = SIZE_MAX;
  for (size_t k = i; k < j; k++) {
    size_t q = recursiveMatrixChain(p, i, k) + recursiveMatrixChain(p, k + 1, j) +
               p[i - 1] * p[k] * p[j];
    if (q < best) best = q;
  }
  return best;
}
