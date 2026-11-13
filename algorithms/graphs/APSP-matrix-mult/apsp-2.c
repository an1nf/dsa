#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static void extendShortestPaths(const double *A, const double *B, double *out, size_t n) {
  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < n; j++) {
      double best = INFINITY;
      for (size_t k = 0; k < n; k++)
        if (A[i * n + k] + B[k * n + j] < best) best = A[i * n + k] + B[k * n + j];
      out[i * n + j] = best;
    }
}

bool fasterAllPairsShortestPaths(const double *W, size_t n, double *L) {
  double *tmp = malloc(n * n * sizeof *tmp);
  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < n; j++) L[i * n + j] = i == j ? 0 : W[i * n + j];
  for (size_t r = 1; r < n; r *= 2) {
    extendShortestPaths(L, L, tmp, n);
    memcpy(L, tmp, n * n * sizeof *L);
  }
  bool ok = true;
  for (size_t i = 0; i < n; i++)
    if (L[i * n + i] < 0) ok = false;
  free(tmp);
  return ok;
}
