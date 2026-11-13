#include <limits.h>
#include <stddef.h>

int maxSubarray(const int *a, size_t n, size_t *lo, size_t *hi) {
  int best = INT_MIN;
  for (size_t i = 0; i < n; i++) {
    int sum = 0;
    for (size_t j = i; j < n; j++) {
      sum += a[j];
      if (sum > best) {
        best = sum;
        *lo = i;
        *hi = j;
      }
    }
  }
  return best;
}
