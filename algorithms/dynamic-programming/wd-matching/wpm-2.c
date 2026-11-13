#include <stdbool.h>
#include <stdlib.h>

static bool aux(const char *s, size_t i, const char *p, size_t j, size_t m,
                signed char *memo) {
  signed char *c = &memo[i * (m + 1) + j];
  if (*c >= 0) return *c;
  bool r;
  if (j == 0) r = i == 0;
  else if (p[j - 1] == '*')
    r = aux(s, i, p, j - 1, m, memo) || (i > 0 && aux(s, i - 1, p, j, m, memo));
  else
    r = i > 0 && (p[j - 1] == '?' || p[j - 1] == s[i - 1]) &&
        aux(s, i - 1, p, j - 1, m, memo);
  *c = r;
  return r;
}

bool memoizedWildcardMatch(const char *s, size_t n, const char *p, size_t m) {
  signed char *memo = malloc((n + 1) * (m + 1));
  for (size_t k = 0; k < (n + 1) * (m + 1); k++) memo[k] = -1;
  bool r = aux(s, n, p, m, m, memo);
  free(memo);
  return r;
}
