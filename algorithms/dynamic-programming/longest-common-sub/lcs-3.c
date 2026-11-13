#include <stdlib.h>

size_t lcs(const char *x, size_t m, const char *y, size_t n, char *out) {
  size_t C = n + 1;
  size_t *c = calloc((m + 1) * C, sizeof *c);
  for (size_t i = 1; i <= m; i++)
    for (size_t j = 1; j <= n; j++)
      if (x[i - 1] == y[j - 1])
        c[i * C + j] = c[(i - 1) * C + j - 1] + 1;
      else if (c[(i - 1) * C + j] >= c[i * C + j - 1])
        c[i * C + j] = c[(i - 1) * C + j];
      else
        c[i * C + j] = c[i * C + j - 1];

  size_t len = c[m * C + n], k = len;
  for (size_t i = m, j = n; k > 0; ) {
    if (x[i - 1] == y[j - 1]) { out[--k] = x[i - 1]; i--; j--; }
    else if (c[(i - 1) * C + j] >= c[i * C + j - 1]) i--;
    else j--;
  }
  out[len] = '\0';
  free(c);
  return len;
}
