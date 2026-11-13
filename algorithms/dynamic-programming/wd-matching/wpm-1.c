#include <stdbool.h>
#include <stddef.h>

bool wildcardMatch(const char *s, size_t i, const char *p, size_t j) {
  if (j == 0) return i == 0;
  if (p[j - 1] == '*')
    return wildcardMatch(s, i, p, j - 1) || (i > 0 && wildcardMatch(s, i - 1, p, j));
  return i > 0 && (p[j - 1] == '?' || p[j - 1] == s[i - 1]) &&
         wildcardMatch(s, i - 1, p, j - 1);
}
