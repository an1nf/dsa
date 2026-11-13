#include <stddef.h>

size_t lcsLength(const char *x, size_t m, const char *y, size_t n) {
  if (m == 0 || n == 0) return 0;
  if (x[m - 1] == y[n - 1]) return 1 + lcsLength(x, m - 1, y, n - 1);
  size_t a = lcsLength(x, m - 1, y, n), b = lcsLength(x, m, y, n - 1);
  return a > b ? a : b;
}
