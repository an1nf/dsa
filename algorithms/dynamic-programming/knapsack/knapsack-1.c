#include <stddef.h>

typedef struct { size_t weight; double value; } Item;

double knapsack(const Item *items, size_t n, size_t W) {
  if (n == 0 || W == 0) return 0;
  double skip = knapsack(items, n - 1, W);
  if (items[n - 1].weight > W) return skip;
  double take = items[n - 1].value +
                knapsack(items, n - 1, W - items[n - 1].weight);
  return take > skip ? take : skip;
}
