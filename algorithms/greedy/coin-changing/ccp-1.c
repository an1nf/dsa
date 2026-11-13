#include <stddef.h>

size_t greedyChange(const size_t *coins, size_t k, size_t amount, size_t *count) {
  size_t total = 0;
  for (size_t i = 0; i < k; i++) {
    count[i] = amount / coins[i];
    amount %= coins[i];
    total += count[i];
  }
  return amount == 0 ? total : 0;
}
