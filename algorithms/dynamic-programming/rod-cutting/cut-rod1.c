#include <stddef.h>

double cutRod(const double *p, size_t n) {
  if (n == 0) return 0;
  double q = -1;
  for (size_t i = 1; i <= n; i++) {
    double r = p[i] + cutRod(p, n - i);
    if (r > q) q = r;
  }
  return q;
}
