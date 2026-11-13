#include <stddef.h>
#include <stdint.h>

size_t minJumps(const size_t *jumps, size_t i, size_t n) {
  if (i + 1 >= n) return 0;
  size_t best = SIZE_MAX;
  for (size_t k = 1; k <= jumps[i] && i + k < n; k++) {
    size_t j = minJumps(jumps, i + k, n);
    if (j != SIZE_MAX && j + 1 < best) best = j + 1;
  }
  return best;
}
