#include <stddef.h>

static void rec(const int *A, const int *B, int *C, size_t N, size_t n,
                size_t i, size_t k, size_t j) {
  if (n == 1) {
    C[i * N + j] += A[i * N + k] * B[k * N + j];
    return;
  }
  size_t h = n / 2;
  for (size_t di = 0; di < n; di += h)
    for (size_t dj = 0; dj < n; dj += h)
      for (size_t dk = 0; dk < n; dk += h)
        rec(A, B, C, N, h, i + di, k + dk, j + dj);
}

void matrixMultiply(const int *A, const int *B, int *C, size_t n) {
  for (size_t i = 0; i < n * n; i++) C[i] = 0;
  rec(A, B, C, n, n, 0, 0, 0);
}
