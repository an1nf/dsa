#include <stdint.h>
#include <stdlib.h>

void galeShapley(size_t n, const size_t *proposerPref, const size_t *acceptorPref,
                 size_t *match) {
  size_t *rank = malloc(n * n * sizeof *rank), *next = calloc(n, sizeof *next),
         *partner = malloc(n * sizeof *partner), *free_ = malloc(n * sizeof *free_), top = 0;
  for (size_t a = 0; a < n; a++) {
    partner[a] = SIZE_MAX;
    for (size_t i = 0; i < n; i++) rank[a * n + acceptorPref[a * n + i]] = i;
  }
  for (size_t p = n; p-- > 0; ) free_[top++] = p;
  while (top > 0) {
    size_t p = free_[--top], a = proposerPref[p * n + next[p]++], q = partner[a];
    if (q == SIZE_MAX) partner[a] = p;
    else if (rank[a * n + p] < rank[a * n + q]) {
      partner[a] = p;
      free_[top++] = q;
    } else free_[top++] = p;
  }
  for (size_t a = 0; a < n; a++) match[partner[a]] = a;
  free(rank); free(next); free(partner); free(free_);
}
