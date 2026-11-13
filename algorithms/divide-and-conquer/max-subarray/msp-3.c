#include <limits.h>
#include <stddef.h>

int maxSubarray(const int *a, size_t n, size_t *lo, size_t *hi) {
  int best = INT_MIN, sum = 0;
  size_t start = 0;
  for (size_t i = 0; i < n; i++) {
    sum += a[i];
    if (sum > best) {
      best = sum;
      *lo = start;
      *hi = i;
    }
    if (sum < 0) {
      sum = 0;
      start = i + 1;
    }
  }
  return best;
}
