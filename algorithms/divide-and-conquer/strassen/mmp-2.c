#include <stdlib.h>

static void quadrant(const int *M, size_t n, int r, int c, int *Q) {
  size_t h = n / 2;
  for (size_t i = 0; i < h; i++)
    for (size_t j = 0; j < h; j++)
      Q[i * h + j] = M[(i + r * h) * n + j + c * h];
}

static void add(const int *X, const int *Y, int *Z, size_t m, int sign) {
  for (size_t i = 0; i < m; i++) Z[i] = X[i] + sign * Y[i];
}

void strassen(const int *A, const int *B, int *C, size_t n) {
  if (n == 1) {
    C[0] = A[0] * B[0];
    return;
  }
  size_t h = n / 2, m = h * h;
  int *buf = malloc(19 * m * sizeof *buf);
  int *a[4], *b[4], *P[7], *S = buf + 15 * m, *T = buf + 16 * m;
  for (int q = 0; q < 4; q++) {
    a[q] = buf + q * m;
    b[q] = buf + (4 + q) * m;
    quadrant(A, n, q / 2, q % 2, a[q]);
    quadrant(B, n, q / 2, q % 2, b[q]);
  }
  for (int p = 0; p < 7; p++) P[p] = buf + (8 + p) * m;

  add(b[1], b[3], T, m, -1); strassen(a[0], T, P[0], h);
  add(a[0], a[1], S, m, +1); strassen(S, b[3], P[1], h);
  add(a[2], a[3], S, m, +1); strassen(S, b[0], P[2], h);
  add(b[2], b[0], T, m, -1); strassen(a[3], T, P[3], h);
  add(a[0], a[3], S, m, +1); add(b[0], b[3], T, m, +1); strassen(S, T, P[4], h);
  add(a[1], a[3], S, m, -1); add(b[2], b[3], T, m, +1); strassen(S, T, P[5], h);
  add(a[0], a[2], S, m, -1); add(b[0], b[1], T, m, +1); strassen(S, T, P[6], h);

  for (size_t i = 0; i < h; i++)
    for (size_t j = 0; j < h; j++) {
      size_t k = i * h + j;
      C[i * n + j] = P[4][k] + P[3][k] - P[1][k] + P[5][k];
      C[i * n + j + h] = P[0][k] + P[1][k];
      C[(i + h) * n + j] = P[2][k] + P[3][k];
      C[(i + h) * n + j + h] = P[4][k] + P[0][k] - P[2][k] - P[6][k];
    }
  free(buf);
}
