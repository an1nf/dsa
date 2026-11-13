#include <stdlib.h>

double bottomUpCutRod(const double *p, size_t n) {
  double *r = malloc((n + 1) * sizeof *r);
  r[0] = 0;
  for (size_t j = 1; j <= n; j++) {
    r[j] = -1;
    for (size_t i = 1; i <= j; i++)
      if (p[i] + r[j - i] > r[j]) r[j] = p[i] + r[j - i];
  }
  double q = r[n];
  free(r);
  return q;
}
