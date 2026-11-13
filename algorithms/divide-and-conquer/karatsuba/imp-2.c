#include <stdlib.h>

static void rec(const long long *x, const long long *y, long long *z, size_t n) {
  for (size_t i = 0; i < 2 * n; i++) z[i] = 0;
  if (n == 1) {
    z[0] = x[0] * y[0];
    return;
  }
  size_t k = n / 2, h = n - k;
  long long *xs = calloc(h, sizeof *xs), *ys = calloc(h, sizeof *ys);
  long long *z0 = malloc(2 * k * sizeof *z0), *z1 = malloc(2 * h * sizeof *z1),
            *z2 = malloc(2 * h * sizeof *z2);
  for (size_t i = 0; i < h; i++) {
    xs[i] = x[k + i] + (i < k ? x[i] : 0);
    ys[i] = y[k + i] + (i < k ? y[i] : 0);
  }
  rec(x, y, z0, k);
  rec(x + k, y + k, z2, h);
  rec(xs, ys, z1, h);
  for (size_t i = 0; i < 2 * h; i++) z1[i] -= z2[i] + (i < 2 * k ? z0[i] : 0);
  for (size_t i = 0; i < 2 * k; i++) z[i] += z0[i];
  for (size_t i = 0; i < 2 * h; i++) {
    z[k + i] += z1[i];
    if (2 * k + i < 2 * n) z[2 * k + i] += z2[i];
  }
  free(xs); free(ys); free(z0); free(z1); free(z2);
}

void karatsuba(const int *x, const int *y, int *z, size_t n) {
  long long *a = malloc(n * sizeof *a), *b = malloc(n * sizeof *b),
            *c = malloc(2 * n * sizeof *c);
  for (size_t i = 0; i < n; i++) { a[i] = x[i]; b[i] = y[i]; }
  rec(a, b, c, n);
  long long carry = 0;
  for (size_t i = 0; i < 2 * n; i++) {
    carry += c[i];
    z[i] = (int)(carry % 10);
    carry /= 10;
  }
  free(a); free(b); free(c);
}
