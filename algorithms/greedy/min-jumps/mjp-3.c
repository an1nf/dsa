#include <stddef.h>
#include <stdint.h>

size_t minJumps(const size_t *jumps, size_t n, size_t *path) {
  size_t count = 0, reach = 0, next = 0, best = 0;
  for (size_t i = 0; i + 1 < n; i++) {
    if (i + jumps[i] > next) { next = i + jumps[i]; best = i; }
    if (i == reach) {
      if (next <= i) return SIZE_MAX;
      path[count++] = best;
      reach = next;
      if (reach >= n - 1) break;
    }
  }
  return count;
}
