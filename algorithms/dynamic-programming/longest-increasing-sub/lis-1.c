#include <stddef.h>
#include <stdint.h>

static size_t aux(const int *a, size_t i, size_t bound) {
  if (i == 0) return 0;
  size_t skip = aux(a, i - 1, bound);
  if (bound != SIZE_MAX && a[i - 1] > a[bound]) return skip;
  size_t take = 1 + aux(a, i - 1, i - 1);
  return take > skip ? take : skip;
}

size_t lisLength(const int *a, size_t n) {
  return aux(a, n, SIZE_MAX);
}
