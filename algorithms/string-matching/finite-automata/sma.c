#include <stdlib.h>
#include <string.h>

#define SIGMA 256

size_t *computeTransitionFunction(const char *P, size_t m) {
  size_t *delta = malloc((m + 1) * SIGMA * sizeof *delta);
  char *buf = malloc(m + 1);
  memcpy(buf, P, m);
  for (size_t q = 0; q <= m; q++) {
    for (int a = 0; a < SIGMA; a++) {
      buf[q] = (char)a;
      size_t k = q + 1 < m ? q + 1 : m;
      while (k > 0 && memcmp(P, buf + q + 1 - k, k) != 0) k--;
      delta[q * SIGMA + a] = k;
    }
    if (q < m) buf[q] = P[q];
  }
  free(buf);
  return delta;
}

size_t finiteAutomatonMatcher(const char *T, size_t n, const size_t *delta, size_t m,
                              size_t *shifts) {
  size_t count = 0;
  for (size_t i = 0, q = 0; i < n; i++) {
    q = delta[q * SIGMA + (unsigned char)T[i]];
    if (q == m) shifts[count++] = i + 1 - m;
  }
  return count;
}
