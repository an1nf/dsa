#include <stdlib.h>
#include <string.h>

typedef enum { COPY, INSERT, DELETE, REPLACE, TWIDDLE, KILL } Op;

size_t editSequence(const char *x, const char *y, const size_t *cost,
                    Op *seq, size_t *len) {
  size_t m = strlen(x), n = strlen(y), N = n + 1;
  size_t *c = malloc((m + 1) * N * sizeof *c);
  Op *op = malloc((m + 1) * N * sizeof *op);
  for (size_t i = 0; i <= m; i++) { c[i * N] = i * cost[DELETE]; op[i * N] = DELETE; }
  for (size_t j = 0; j <= n; j++) { c[j] = j * cost[INSERT]; op[j] = INSERT; }

  for (size_t i = 1; i <= m; i++)
    for (size_t j = 1; j <= n; j++) {
      size_t k = i * N + j, d;
      Op o = x[i - 1] == y[j - 1] ? COPY : REPLACE;
      c[k] = c[k - N - 1] + cost[o];
      op[k] = o;
      if (i > 1 && j > 1 && x[i - 1] == y[j - 2] && x[i - 2] == y[j - 1] &&
          (d = c[k - 2 * N - 2] + cost[TWIDDLE]) < c[k]) { c[k] = d; op[k] = TWIDDLE; }
      if ((d = c[k - 1] + cost[INSERT]) < c[k]) { c[k] = d; op[k] = INSERT; }
      if ((d = c[k - N] + cost[DELETE]) < c[k]) { c[k] = d; op[k] = DELETE; }
    }

  size_t best = c[m * N + n], killFrom = m;
  for (size_t i = 0; i < m; i++)
    if (c[i * N + n] + cost[KILL] < best) { best = c[i * N + n] + cost[KILL]; killFrom = i; }

  size_t s = 0, i = killFrom, j = n;
  if (killFrom < m) seq[s++] = KILL;
  while (i > 0 || j > 0) {
    Op o = op[i * N + j];
    seq[s++] = o;
    if (o == INSERT) j--;
    else if (o == DELETE) i--;
    else if (o == TWIDDLE) { i -= 2; j -= 2; }
    else { i--; j--; }
  }
  for (size_t a = 0, b = s; a + 1 < b--; a++) { Op t = seq[a]; seq[a] = seq[b]; seq[b] = t; }
  *len = s;
  free(c);
  free(op);
  return best;
}
