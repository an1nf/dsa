#include <string.h>

size_t naiveStringMatcher(const char *T, size_t n, const char *P, size_t m, size_t *shifts) {
  size_t count = 0;
  for (size_t s = 0; s + m <= n; s++)
    if (memcmp(T + s, P, m) == 0) shifts[count++] = s;
  return count;
}
