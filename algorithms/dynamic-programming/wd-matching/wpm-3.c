#include <stdbool.h>
#include <stdlib.h>

bool wildcardMatch(const char *s, size_t n, const char *p, size_t m) {
  size_t M = m + 1;
  bool *T = calloc((n + 1) * M, sizeof *T);
  T[0] = true;
  for (size_t j = 1; j <= m; j++) T[j] = p[j - 1] == '*' && T[j - 1];
  for (size_t i = 1; i <= n; i++)
    for (size_t j = 1; j <= m; j++)
      if (p[j - 1] == '*')
        T[i * M + j] = T[i * M + j - 1] || T[(i - 1) * M + j];
      else
        T[i * M + j] = (p[j - 1] == '?' || p[j - 1] == s[i - 1]) &&
                       T[(i - 1) * M + j - 1];
  bool r = T[n * M + m];
  free(T);
  return r;
}
