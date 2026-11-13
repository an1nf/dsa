#include <stdlib.h>

typedef struct { double weight, value; } Item;

static void swap(Item *x, Item *y) { Item t = *x; *x = *y; *y = t; }

static void arrange(Item *a, size_t lo, size_t hi, double W) {
  while (lo < hi) {
    swap(&a[lo + (size_t)rand() % (hi - lo)], &a[hi - 1]);
    double r = a[hi - 1].value / a[hi - 1].weight, wGreater = 0, wEqual = 0;
    size_t gt = lo, i = lo, lt = hi;
    while (i < lt) {
      double q = a[i].value / a[i].weight;
      if (q > r) { wGreater += a[i].weight; swap(&a[gt++], &a[i++]); }
      else if (q < r) swap(&a[i], &a[--lt]);
      else { wEqual += a[i].weight; i++; }
    }
    if (wGreater > W) hi = gt;
    else if (wGreater + wEqual >= W) return;
    else { W -= wGreater + wEqual; lo = lt; }
  }
}

double fractionalKnapsack(Item *items, size_t n, double W, size_t *full, double *frac) {
  arrange(items, 0, n, W);
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
