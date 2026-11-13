#include <stdlib.h>

typedef struct { double weight, value; } Item;

static int byRatioDesc(const void *a, const void *b) {
  const Item *x = a, *y = b;
  double d = y->value / y->weight - x->value / x->weight;
  return (d > 0) - (d < 0);
}

double fractionalKnapsack(Item *items, size_t n, double W, size_t *full, double *frac) {
  qsort(items, n, sizeof *items, byRatioDesc);
  double value = 0;
  size_t i = 0;
  for (; i < n && items[i].weight <= W; i++) {
    W -= items[i].weight;
    value += items[i].value;
  }
  *full = i;
  *frac = i < n ? W / items[i].weight : 0;
  return value + (i < n ? *frac * items[i].value : 0);
}
