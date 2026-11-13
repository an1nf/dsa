#include <float.h>
#include <stddef.h>

double optimalBstCost(const double *p, size_t i, size_t j) {
  if (i == j) return 0;
  double best = DBL_MAX, w = 0;
  for (size_t r = i; r < j; r++) {
    w += p[r];
    double c = optimalBstCost(p, i, r) + optimalBstCost(p, r + 1, j);
    if (c < best) best = c;
  }
  return best + w;
}
