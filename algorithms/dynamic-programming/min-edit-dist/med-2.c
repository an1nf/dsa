#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef enum { COPY, INSERT, DELETE, REPLACE, TWIDDLE, KILL } Op;

static size_t dist(const char *x, size_t i, const char *y, size_t j, size_t n,
                   const size_t *cost, size_t *memo) {
  size_t *m = &memo[i * (n + 1) + j];
  if (*m != SIZE_MAX) return *m;
  if (i == 0) return *m = j * cost[INSERT];
  if (j == 0) return *m = i * cost[DELETE];
  size_t best, d;
  best = dist(x, i - 1, y, j - 1, n, cost, memo) +
         cost[x[i - 1] == y[j - 1] ? COPY : REPLACE];
  if (i > 1 && j > 1 && x[i - 1] == y[j - 2] && x[i - 2] == y[j - 1] &&
      (d = dist(x, i - 2, y, j - 2, n, cost, memo) + cost[TWIDDLE]) < best) best = d;
  if ((d = dist(x, i, y, j - 1, n, cost, memo) + cost[INSERT]) < best) best = d;
  if ((d = dist(x, i - 1, y, j, n, cost, memo) + cost[DELETE]) < best) best = d;
  return *m = best;
}

size_t memoizedEditDistance(const char *x, const char *y, const size_t *cost) {
  size_t m = strlen(x), n = strlen(y), cells = (m + 1) * (n + 1);
  size_t *memo = malloc(cells * sizeof *memo);
  for (size_t i = 0; i < cells; i++) memo[i] = SIZE_MAX;
  size_t best = dist(x, m, y, n, n, cost, memo);
  for (size_t k = 0; k < m; k++) {
    size_t d = dist(x, k, y, n, n, cost, memo) + cost[KILL];
    if (d < best) best = d;
  }
  free(memo);
  return best;
}
