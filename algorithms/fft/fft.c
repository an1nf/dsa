#include <complex.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

static void bitReverseCopy(complex double *a, size_t n) {
  for (size_t i = 1, j = 0; i < n; i++) {
    size_t bit = n >> 1;
    for (; j & bit; bit >>= 1) j ^= bit;
    j |= bit;
    if (i < j) { complex double t = a[i]; a[i] = a[j]; a[j] = t; }
  }
}

void fft(complex double *a, size_t n, int inverse) {
  bitReverseCopy(a, n);
  for (size_t m = 2; m <= n; m <<= 1) {
    complex double wm = cexp((inverse ? -2 : 2) * PI * I / (double)m);
    for (size_t k = 0; k < n; k += m) {
      complex double w = 1;
      for (size_t j = 0; j < m / 2; j++) {
        complex double t = w * a[k + j + m / 2], u = a[k + j];
        a[k + j] = u + t;
        a[k + j + m / 2] = u - t;
        w *= wm;
      }
    }
  }
  if (inverse)
    for (size_t i = 0; i < n; i++) a[i] /= (double)n;
}

double *polyMultiply(const double *x, size_t nx, const double *y, size_t ny) {
  size_t n = 1;
  while (n < nx + ny) n <<= 1;
  complex double *a = calloc(n, sizeof *a), *b = calloc(n, sizeof *b);
  for (size_t i = 0; i < nx; i++) a[i] = x[i];
  for (size_t i = 0; i < ny; i++) b[i] = y[i];
  fft(a, n, 0);
  fft(b, n, 0);
  for (size_t i = 0; i < n; i++) a[i] *= b[i];
  fft(a, n, 1);
  double *c = malloc((nx + ny - 1) * sizeof *c);
  for (size_t i = 0; i + 1 < nx + ny; i++) c[i] = creal(a[i]);
  free(a);
  free(b);
  return c;
}
