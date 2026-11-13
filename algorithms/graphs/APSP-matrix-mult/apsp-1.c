#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static void extendShortestPaths(const double *L, const double *W, double *out, size_t n) {
  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < n; j++) {
      double best = INFINITY;
      for (size_t k = 0; k < n; k++)
        if (L[i * n + k] + W[k * n + j] < best) best = L[i * n + k] + W[k * n + j];
      out[i * n + j] = best;
    }
}

bool slowAllPairsShortestPaths(const double *W, size_t n, double *L) {
  double *W0 = malloc(n * n * sizeof *W0), *tmp = malloc(n * n * sizeof *tmp);
  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < n; j++) W0[i * n + j] = i == j ? 0 : W[i * n + j];
  memcpy(L, W0, n * n * sizeof *L);
  for (size_t r = 1; r < n; r++) {
    extendShortestPaths(L, W0, tmp, n);
    memcpy(L, tmp, n * n * sizeof *L);
  }
  extendShortestPaths(L, W0, tmp, n);
  bool ok = true;
  for (size_t i = 0; i < n * n; i++)
    if (tmp[i] < L[i]) ok = false;
  free(W0);
  free(tmp);
  return ok;
}
