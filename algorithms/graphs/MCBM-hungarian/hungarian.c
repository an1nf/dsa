#include <float.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

double hungarian(size_t n, const double *w, size_t *match) {
  double *hl = malloc(n * sizeof *hl), *hr = calloc(n, sizeof *hr), *slack = malloc(n * sizeof *slack);
  size_t *matchR = malloc(n * sizeof *matchR), *way = malloc(n * sizeof *way);
  bool *usedR = malloc(n * sizeof *usedR);
  for (size_t l = 0; l < n; l++) {
    hl[l] = -DBL_MAX;
    for (size_t r = 0; r < n; r++)
      if (w[l * n + r] > hl[l]) hl[l] = w[l * n + r];
    match[l] = SIZE_MAX;
  }
  for (size_t r = 0; r < n; r++) matchR[r] = SIZE_MAX;

  for (size_t root = 0; root < n; root++) {
    for (size_t r = 0; r < n; r++) { slack[r] = DBL_MAX; usedR[r] = false; }
    size_t l = root, r0 = SIZE_MAX;
    for (;;) {
      double delta = DBL_MAX;
      size_t next = SIZE_MAX;
      for (size_t r = 0; r < n; r++) {
        if (usedR[r]) continue;
        double s = hl[l] + hr[r] - w[l * n + r];
        if (s < slack[r]) { slack[r] = s; way[r] = r0; }
        if (slack[r] < delta) { delta = slack[r]; next = r; }
      }
      hl[root] -= delta;
      for (size_t r = 0; r < n; r++)
        if (usedR[r]) { hl[matchR[r]] -= delta; hr[r] += delta; }
        else slack[r] -= delta;
      usedR[next] = true;
      if (matchR[next] == SIZE_MAX) { r0 = next; break; }
      r0 = next;
      l = matchR[next];
    }
    for (size_t r = r0; r != SIZE_MAX; ) {
      size_t prev = way[r];
      matchR[r] = prev == SIZE_MAX ? root : matchR[prev];
      r = prev;
    }
  }
  double total = 0;
  for (size_t r = 0; r < n; r++) {
    match[matchR[r]] = r;
    total += w[matchR[r] * n + r];
  }
  free(hl); free(hr); free(slack); free(matchR); free(way); free(usedR);
  return total;
}
