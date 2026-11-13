#include <stdint.h>
#include <stdlib.h>

static size_t aux(const char *x, size_t i, const char *y, size_t j,
                  size_t n, size_t *c) {
  size_t *m = &c[i * (n + 1) + j];
  if (*m != SIZE_MAX) return *m;
  if (i == 0 || j == 0) return *m = 0;
  if (x[i - 1] == y[j - 1]) return *m = 1 + aux(x, i - 1, y, j - 1, n, c);
  size_t a = aux(x, i - 1, y, j, n, c), b = aux(x, i, y, j - 1, n, c);
  return *m = a > b ? a : b;
}

size_t memoizedLcs(const char *x, size_t m, const char *y, size_t n, char *out) {
  size_t *c = malloc((m + 1) * (n + 1) * sizeof *c);
  for (size_t i = 0; i < (m + 1) * (n + 1); i++) c[i] = SIZE_MAX;
  size_t len = aux(x, m, y, n, n, c), k = len;
  for (size_t i = m, j = n; k > 0; ) {
    if (x[i - 1] == y[j - 1]) { out[--k] = x[i - 1]; i--; j--; }
    else if (aux(x, i - 1, y, j, n, c) >= aux(x, i, y, j - 1, n, c)) i--;
    else j--;
  }
  out[len] = '\0';
  free(c);
  return len;
}
