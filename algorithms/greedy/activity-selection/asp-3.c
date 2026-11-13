#include <stddef.h>

size_t greedyActivitySelector(const size_t *s, const size_t *f, size_t n, size_t *out) {
  if (n == 0) return 0;
  size_t count = 0, k = 0;
  out[count++] = 0;
  for (size_t m = 1; m < n; m++)
    if (s[m] >= f[k]) {
      out[count++] = m;
      k = m;
    }
  return count;
}
