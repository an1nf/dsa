#include <stdlib.h>

typedef struct { size_t weight; double value; } Item;

static double aux(const Item *items, size_t n, size_t w, size_t W, double *memo) {
  double *m = &memo[n * (W + 1) + w];
  if (*m >= 0) return *m;
  if (n == 0 || w == 0) return *m = 0;
  double best = aux(items, n - 1, w, W, memo);
  if (items[n - 1].weight <= w) {
    double take = items[n - 1].value +
                  aux(items, n - 1, w - items[n - 1].weight, W, memo);
    if (take > best) best = take;
  }
  return *m = best;
}

double memoizedKnapsack(const Item *items, size_t n, size_t W) {
  size_t cells = (n + 1) * (W + 1);
  double *memo = malloc(cells * sizeof *memo);
  for (size_t i = 0; i < cells; i++) memo[i] = -1;
  double best = aux(items, n, W, W, memo);
  free(memo);
  return best;
}
