#include <limits.h>
#include <stddef.h>

typedef struct { size_t lo, hi; int sum; } Sub;

static Sub maxCrossing(const int *a, size_t lo, size_t mid, size_t hi) {
  Sub s = {mid, mid + 1, 0};
  int sum = 0, left = INT_MIN, right = INT_MIN;
  for (size_t i = mid + 1; i-- > lo; ) {
    sum += a[i];
    if (sum > left) { left = sum; s.lo = i; }
  }
  sum = 0;
  for (size_t j = mid + 1; j <= hi; j++) {
    sum += a[j];
    if (sum > right) { right = sum; s.hi = j; }
  }
  s.sum = left + right;
  return s;
}

Sub maxSubarray(const int *a, size_t lo, size_t hi) {
  if (lo == hi) return (Sub){lo, hi, a[lo]};
  size_t mid = lo + (hi - lo) / 2;
  Sub l = maxSubarray(a, lo, mid);
  Sub r = maxSubarray(a, mid + 1, hi);
  Sub c = maxCrossing(a, lo, mid, hi);
  if (l.sum >= r.sum && l.sum >= c.sum) return l;
  return r.sum >= c.sum ? r : c;
}
