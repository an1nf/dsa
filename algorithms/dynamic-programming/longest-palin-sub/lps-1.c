#include <stddef.h>

size_t lpsLength(const char *s, size_t i, size_t j) {
  if (i > j) return 0;
  if (i == j) return 1;
  if (s[i] == s[j]) return 2 + lpsLength(s, i + 1, j - 1);
  size_t a = lpsLength(s, i + 1, j), b = lpsLength(s, i, j - 1);
  return a > b ? a : b;
}
