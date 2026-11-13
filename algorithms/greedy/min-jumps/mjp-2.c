#include <stdint.h>
#include <stdlib.h>

size_t minJumps(const size_t *jumps, size_t n, size_t *path) {
  if (n <= 1) return 0;
  size_t *d = malloc(n * sizeof *d), *from = malloc(n * sizeof *from);
  d[0] = 0;
  for (size_t i = 1; i < n; i++) {
    d[i] = SIZE_MAX;
    for (size_t j = 0; j < i; j++)
      if (d[j] != SIZE_MAX && j + jumps[j] >= i && d[j] + 1 < d[i]) {
        d[i] = d[j] + 1;
        from[i] = j;
      }
  }
  size_t best = d[n - 1];
  if (best != SIZE_MAX)
    for (size_t i = n - 1, k = best; k > 0; i = from[i]) path[--k] = from[i];
  free(d);
  free(from);
  return best;
}
