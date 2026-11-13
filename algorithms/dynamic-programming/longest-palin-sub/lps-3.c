#include <stdlib.h>

size_t lps(const char *s, size_t n, char *out) {
  if (n == 0) { out[0] = '\0'; return 0; }
  size_t *L = calloc(n * n, sizeof *L);
  for (size_t i = 0; i < n; i++) L[i * n + i] = 1;
  for (size_t d = 1; d < n; d++)
    for (size_t i = 0; i + d < n; i++) {
      size_t j = i + d;
      if (s[i] == s[j])
        L[i * n + j] = 2 + (d > 1 ? L[(i + 1) * n + j - 1] : 0);
      else
        L[i * n + j] = L[(i + 1) * n + j] > L[i * n + j - 1]
                     ? L[(i + 1) * n + j] : L[i * n + j - 1];
    }

  size_t len = L[n - 1], l = 0, r = len;
  for (size_t i = 0, j = n - 1; i <= j && l < r; ) {
    if (i == j) { out[l++] = s[i]; break; }
    if (s[i] == s[j]) { out[l++] = out[--r] = s[i]; i++; j--; }
    else if (L[(i + 1) * n + j] >= L[i * n + j - 1]) i++;
    else j--;
  }
  out[len] = '\0';
  free(L);
  return len;
}
