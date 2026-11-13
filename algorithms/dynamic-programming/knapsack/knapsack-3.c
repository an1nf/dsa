#include <stdbool.h>
#include <stdlib.h>

typedef struct { size_t weight; double value; } Item;

double knapsack(const Item *items, size_t n, size_t W, bool *taken) {
  size_t C = W + 1;
  double *K = calloc((n + 1) * C, sizeof *K);
  for (size_t i = 1; i <= n; i++)
    for (size_t w = 0; w <= W; w++) {
      K[i * C + w] = K[(i - 1) * C + w];
      if (items[i - 1].weight <= w) {
        double take = K[(i - 1) * C + w - items[i - 1].weight] + items[i - 1].value;
        if (take > K[i * C + w]) K[i * C + w] = take;
      }
    }
  double best = K[n * C + W];
  for (size_t i = n, w = W; i > 0; i--) {
    taken[i - 1] = K[i * C + w] != K[(i - 1) * C + w];
    if (taken[i - 1]) w -= items[i - 1].weight;
  }
  free(K);
  return best;
}
