#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

void transitiveClosureByDistances(const bool *A, size_t n, bool *T) {
  double *D = malloc(n * n * sizeof *D);
  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < n; j++)
      D[i * n + j] = i == j ? 0 : A[i * n + j] ? 1 : INFINITY;
  for (size_t k = 0; k < n; k++)
    for (size_t i = 0; i < n; i++)
      for (size_t j = 0; j < n; j++)
        if (D[i * n + k] + D[k * n + j] < D[i * n + j])
          D[i * n + j] = D[i * n + k] + D[k * n + j];
  for (size_t i = 0; i < n * n; i++) T[i] = !isinf(D[i]);
  free(D);
}
