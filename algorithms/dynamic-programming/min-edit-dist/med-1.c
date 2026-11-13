#include <string.h>

typedef enum { COPY, INSERT, DELETE, REPLACE, TWIDDLE, KILL } Op;

static size_t dist(const char *x, size_t i, const char *y, size_t j,
                   const size_t *cost) {
  if (i == 0) return j * cost[INSERT];
  if (j == 0) return i * cost[DELETE];
  size_t best, d;
  if (x[i - 1] == y[j - 1]) best = dist(x, i - 1, y, j - 1, cost) + cost[COPY];
  else best = dist(x, i - 1, y, j - 1, cost) + cost[REPLACE];
  if (i > 1 && j > 1 && x[i - 1] == y[j - 2] && x[i - 2] == y[j - 1] &&
      (d = dist(x, i - 2, y, j - 2, cost) + cost[TWIDDLE]) < best) best = d;
  if ((d = dist(x, i, y, j - 1, cost) + cost[INSERT]) < best) best = d;
  if ((d = dist(x, i - 1, y, j, cost) + cost[DELETE]) < best) best = d;
  return best;
}

size_t editDistance(const char *x, const char *y, const size_t *cost) {
  size_t m = strlen(x), n = strlen(y), best = dist(x, m, y, n, cost);
  for (size_t k = 0; k < m; k++) {
    size_t d = dist(x, k, y, n, cost) + cost[KILL];
    if (d < best) best = d;
  }
  return best;
}
