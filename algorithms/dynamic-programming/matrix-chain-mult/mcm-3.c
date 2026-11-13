#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

size_t matrixChainOrder(const size_t *p, size_t n, size_t *s) {
  size_t N = n + 1;
  size_t *m = calloc(N * N, sizeof *m);
  for (size_t l = 2; l <= n; l++)
    for (size_t i = 1; i + l - 1 <= n; i++) {
      size_t j = i + l - 1;
      m[i * N + j] = SIZE_MAX;
      for (size_t k = i; k < j; k++) {
        size_t q = m[i * N + k] + m[(k + 1) * N + j] + p[i - 1] * p[k] * p[j];
        if (q < m[i * N + j]) {
          m[i * N + j] = q;
          s[i * N + j] = k;
        }
      }
    }
  size_t cost = m[1 * N + n];
  free(m);
  return cost;
}

char *optimalParens(const size_t *s, size_t n, size_t i, size_t j, char *out) {
  if (i == j) return out + sprintf(out, "A%zu", i);
  *out++ = '(';
  out = optimalParens(s, n, i, s[i * (n + 1) + j], out);
  out = optimalParens(s, n, s[i * (n + 1) + j] + 1, j, out);
  *out++ = ')';
  *out = '\0';
  return out;
}
