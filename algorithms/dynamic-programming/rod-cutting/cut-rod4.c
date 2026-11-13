#include <stddef.h>

double extendedBottomUpCutRod(const double *p, size_t n, double *r, size_t *s) {
  r[0] = 0;
  for (size_t j = 1; j <= n; j++) {
    r[j] = -1;
    for (size_t i = 1; i <= j; i++)
      if (p[i] + r[j - i] > r[j]) {
        r[j] = p[i] + r[j - i];
        s[j] = i;
      }
  }
  return r[n];
}

size_t cutRodSolution(const size_t *s, size_t n, size_t *cuts) {
  size_t k = 0;
  for (; n > 0; n -= s[n]) cuts[k++] = s[n];
  return k;
}
