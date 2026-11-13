#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

static size_t greedyCount(const size_t *coins, size_t k, size_t v) {
  size_t total = 0;
  for (size_t i = 0; i < k; i++) {
    total += v / coins[i];
    v %= coins[i];
  }
  return v == 0 ? total : SIZE_MAX;
}

bool isCanonical(const size_t *coins, size_t k) {
  if (k < 2) return true;
  size_t limit = coins[0] + coins[1];
  size_t *c = malloc((limit + 1) * sizeof *c);
  bool canonical = true;
  c[0] = 0;
  for (size_t v = 1; v <= limit && canonical; v++) {
    c[v] = SIZE_MAX;
    for (size_t i = 0; i < k; i++)
      if (coins[i] <= v && c[v - coins[i]] != SIZE_MAX && c[v - coins[i]] + 1 < c[v])
        c[v] = c[v - coins[i]] + 1;
    canonical = greedyCount(coins, k, v) == c[v];
  }
  free(c);
  return canonical;
}
