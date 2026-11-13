#include <stdbool.h>
#include <stdlib.h>

static bool *palindromeTable(const char *s, size_t n) {
  bool *P = calloc(n * n, sizeof *P);
  for (size_t i = n; i--; )
    for (size_t j = i; j < n; j++)
      P[i * n + j] = s[i] == s[j] && (j - i < 2 || P[(i + 1) * n + j - 1]);
  return P;
}

static size_t cuts(const bool *P, size_t n, size_t i) {
  if (P[i]) return 0;
  size_t best = i;
  for (size_t j = 0; j < i; j++)
    if (P[(j + 1) * n + i]) {
      size_t c = 1 + cuts(P, n, j);
      if (c < best) best = c;
    }
  return best;
}

size_t minPalindromeCuts(const char *s, size_t n) {
  if (n == 0) return 0;
  bool *P = palindromeTable(s, n);
  size_t c = cuts(P, n, n - 1);
  free(P);
  return c;
}
