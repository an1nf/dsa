#include <stdbool.h>
#include <stdlib.h>

bool wildcardMatch(const char *s, size_t n, const char *p, size_t m) {
  bool *T = calloc(m + 1, sizeof *T);
  T[0] = true;
  for (size_t j = 1; j <= m; j++) T[j] = p[j - 1] == '*' && T[j - 1];
  for (size_t i = 1; i <= n; i++) {
    bool diag = T[0];
    T[0] = false;
    for (size_t j = 1; j <= m; j++) {
      bool up = T[j];
      if (p[j - 1] == '*') T[j] = T[j - 1] || up;
      else T[j] = (p[j - 1] == '?' || p[j - 1] == s[i - 1]) && diag;
      diag = up;
    }
  }
  bool r = T[m];
  free(T);
  return r;
}
