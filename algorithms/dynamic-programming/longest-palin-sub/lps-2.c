#include <stdlib.h>

static size_t aux(const char *s, size_t n, long i, long j, size_t *memo) {
  if (i > j) return 0;
  size_t *m = &memo[i * n + j];
  if (*m) return *m;
  if (i == j) return *m = 1;
  if (s[i] == s[j]) return *m = 2 + aux(s, n, i + 1, j - 1, memo);
  size_t a = aux(s, n, i + 1, j, memo), b = aux(s, n, i, j - 1, memo);
  return *m = a > b ? a : b;
}

size_t memoizedLps(const char *s, size_t n, char *out) {
  if (n == 0) { out[0] = '\0'; return 0; }
  size_t *memo = calloc(n * n, sizeof *memo);
  size_t len = aux(s, n, 0, (long)n - 1, memo), l = 0, r = len;
  for (long i = 0, j = (long)n - 1; i <= j; ) {
    if (i == j) { out[l++] = s[i]; break; }
    if (s[i] == s[j]) { out[l++] = out[--r] = s[i]; i++; j--; }
    else if (aux(s, n, i + 1, j, memo) >= aux(s, n, i, j - 1, memo)) i++;
    else j--;
  }
  out[len] = '\0';
  free(memo);
  return len;
}
