#include <float.h>
#include <stdlib.h>

static double aux(const double *p, size_t n, size_t i, size_t j, double *e) {
  double *m = &e[i * (n + 1) + j];
  if (*m >= 0) return *m;
  if (i == j) return *m = 0;
  double best = DBL_MAX, w = 0;
  for (size_t r = i; r < j; r++) {
    w += p[r];
    double c = aux(p, n, i, r, e) + aux(p, n, r + 1, j, e);
    if (c < best) best = c;
  }
  return *m = best + w;
}

double memoizedOptimalBst(const double *p, size_t n) {
  double *e = malloc((n + 1) * (n + 1) * sizeof *e);
  for (size_t i = 0; i < (n + 1) * (n + 1); i++) e[i] = -1;
  double cost = aux(p, n, 0, n, e);
  free(e);
  return cost;
}
