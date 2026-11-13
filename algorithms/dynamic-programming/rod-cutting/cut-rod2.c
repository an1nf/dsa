#include <stdlib.h>

static double aux(const double *p, size_t n, double *r) {
  if (r[n] >= 0) return r[n];
  double q = n == 0 ? 0 : -1;
  for (size_t i = 1; i <= n; i++) {
    double v = p[i] + aux(p, n - i, r);
    if (v > q) q = v;
  }
  return r[n] = q;
}

double memoizedCutRod(const double *p, size_t n) {
  double *r = malloc((n + 1) * sizeof *r);
  for (size_t i = 0; i <= n; i++) r[i] = -1;
  double q = aux(p, n, r);
  free(r);
  return q;
}
