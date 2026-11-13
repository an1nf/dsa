#include <stdbool.h>
#include <stddef.h>

void transitiveClosure(const bool *A, size_t n, bool *T) {
  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < n; j++) T[i * n + j] = i == j || A[i * n + j];
  for (size_t k = 0; k < n; k++)
    for (size_t i = 0; i < n; i++)
      if (T[i * n + k])
        for (size_t j = 0; j < n; j++) T[i * n + j] = T[i * n + j] || T[k * n + j];
}
