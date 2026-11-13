#include <stdlib.h>

size_t *computePrefixFunction(const char *P, size_t m) {
  size_t *pi = malloc(m * sizeof *pi);
  pi[0] = 0;
  for (size_t q = 1, k = 0; q < m; q++) {
    while (k > 0 && P[k] != P[q]) k = pi[k - 1];
    if (P[k] == P[q]) k++;
    pi[q] = k;
  }
  return pi;
}

size_t kmpMatcher(const char *T, size_t n, const char *P, size_t m, size_t *shifts) {
  if (m == 0) return 0;
  size_t *pi = computePrefixFunction(P, m), count = 0;
  for (size_t i = 0, q = 0; i < n; i++) {
    while (q > 0 && P[q] != T[i]) q = pi[q - 1];
    if (P[q] == T[i]) q++;
    if (q == m) {
      shifts[count++] = i + 1 - m;
      q = pi[q - 1];
    }
  }
  free(pi);
  return count;
}
