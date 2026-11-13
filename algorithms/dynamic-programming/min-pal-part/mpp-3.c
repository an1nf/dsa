#include <stdbool.h>
#include <stdlib.h>

size_t palindromePartition(const char *s, size_t n, size_t *ends) {
  if (n == 0) return 0;
  bool *P = calloc(n * n, sizeof *P);
  for (size_t i = n; i--; )
    for (size_t j = i; j < n; j++)
      P[i * n + j] = s[i] == s[j] && (j - i < 2 || P[(i + 1) * n + j - 1]);

  size_t *c = malloc(n * sizeof *c), *split = malloc(n * sizeof *split);
  for (size_t i = 0; i < n; i++) {
    c[i] = i;
    split[i] = i;
    if (P[i]) { c[i] = 0; continue; }
    for (size_t j = 0; j < i; j++)
      if (P[(j + 1) * n + i] && c[j] + 1 < c[i]) {
        c[i] = c[j] + 1;
        split[i] = j;
      }
  }
  size_t cuts = c[n - 1];
  for (size_t i = n - 1, k = cuts + 1; k > 0; i = split[i]) {
    ends[--k] = i;
    if (split[i] == i) break;
  }
  free(P); free(c); free(split);
  return cuts;
}
