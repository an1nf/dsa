#include <stddef.h>

size_t recursiveActivitySelector(const size_t *s, const size_t *f, size_t k,
                                 size_t n, size_t *out) {
  size_t m = k + 1;
  while (m < n && s[m] < f[k]) m++;
  if (m >= n) return 0;
  out[0] = m;
  return 1 + recursiveActivitySelector(s, f, m, n, out + 1);
}

size_t activitySelector(const size_t *s, const size_t *f, size_t n, size_t *out) {
  if (n == 0) return 0;
  out[0] = 0;
  return 1 + recursiveActivitySelector(s, f, 0, n, out + 1);
}
