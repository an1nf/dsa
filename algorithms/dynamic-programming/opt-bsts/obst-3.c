#include <float.h>
#include <stdlib.h>

double optimalBst(const double *p, size_t n) {
  size_t N = n + 1;
  double *e = calloc(N * N, sizeof *e), *w = calloc(N * N, sizeof *w);
  for (size_t l = 1; l <= n; l++)
    for (size_t i = 0; i + l <= n; i++) {
      size_t j = i + l;
      w[i * N + j] = w[i * N + j - 1] + p[j - 1];
      e[i * N + j] = DBL_MAX;
      for (size_t r = i; r < j; r++) {
        double c = e[i * N + r] + e[(r + 1) * N + j] + w[i * N + j];
        if (c < e[i * N + j]) e[i * N + j] = c;
      }
    }
  double cost = e[n];
  free(e);
  free(w);
  return cost;
}
