#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

static bool *palindromeTable(const char *s, size_t n) {
  bool *P = calloc(n * n, sizeof *P);
  for (size_t i = n; i--; )
    for (size_t j = i; j < n; j++)
      P[i * n + j] = s[i] == s[j] && (j - i < 2 || P[(i + 1) * n + j - 1]);
  return P;
}

static size_t cuts(const bool *P, size_t n, size_t i, size_t *memo, size_t *split) {
  if (memo[i] != SIZE_MAX) return memo[i];
  if (P[i]) { split[i] = i; return memo[i] = 0; }
  for (size_t j = 0; j < i; j++)
    if (P[(j + 1) * n + i] && cuts(P, n, j, memo, split) + 1 < memo[i]) {
      memo[i] = memo[j] + 1;
      split[i] = j;
    }
  return memo[i];
}

size_t memoizedPalindromePartition(const char *s, size_t n, size_t *ends) {
  if (n == 0) return 0;
  bool *P = palindromeTable(s, n);
  size_t *memo = malloc(n * sizeof *memo), *split = malloc(n * sizeof *split);
  for (size_t i = 0; i < n; i++) memo[i] = SIZE_MAX;
  size_t c = cuts(P, n, n - 1, memo, split);
  for (size_t i = n - 1, k = c + 1; k > 0; i = split[i]) {
    ends[--k] = i;
    if (split[i] == i) break;
  }
  free(P); free(memo); free(split);
  return c;
}
