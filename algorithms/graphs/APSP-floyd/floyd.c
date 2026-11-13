#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

bool floydWarshall(const double *W, size_t n, double *D, size_t *pred) {
  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < n; j++) {
      D[i * n + j] = i == j ? 0 : W[i * n + j];
      pred[i * n + j] = i == j || isinf(W[i * n + j]) ? SIZE_MAX : i;
    }
  for (size_t k = 0; k < n; k++)
    for (size_t i = 0; i < n; i++)
      for (size_t j = 0; j < n; j++)
        if (D[i * n + k] + D[k * n + j] < D[i * n + j]) {
          D[i * n + j] = D[i * n + k] + D[k * n + j];
          pred[i * n + j] = pred[k * n + j];
        }
  for (size_t i = 0; i < n; i++)
    if (D[i * n + i] < 0) return false;
  return true;
}
