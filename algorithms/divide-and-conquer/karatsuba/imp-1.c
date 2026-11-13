#include <stddef.h>

void multiply(const int *x, size_t n, const int *y, size_t m, int *z) {
  for (size_t i = 0; i < n + m; i++) z[i] = 0;
  for (size_t i = 0; i < n; i++) {
    int carry = 0;
    for (size_t j = 0; j < m; j++) {
      int t = z[i + j] + x[i] * y[j] + carry;
      z[i + j] = t % 10;
      carry = t / 10;
    }
    z[i + m] += carry;
  }
}
