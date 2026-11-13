#include <stdint.h>
#include <stdlib.h>

size_t dpChange(const size_t *coins, size_t k, size_t amount, size_t *last) {
  size_t *c = malloc((amount + 1) * sizeof *c);
  c[0] = 0;
  for (size_t v = 1; v <= amount; v++) {
    c[v] = SIZE_MAX;
    for (size_t i = 0; i < k; i++)
      if (coins[i] <= v && c[v - coins[i]] != SIZE_MAX && c[v - coins[i]] + 1 < c[v]) {
        c[v] = c[v - coins[i]] + 1;
        last[v] = coins[i];
      }
  }
  size_t best = c[amount];
  free(c);
  return best;
}
