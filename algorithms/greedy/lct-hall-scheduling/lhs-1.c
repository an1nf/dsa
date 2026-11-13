#include <stddef.h>

typedef struct { size_t start, end; } Activity;

size_t minHalls(const Activity *a, size_t n) {
  size_t lo = (size_t)-1, hi = 0, best = 0;
  for (size_t i = 0; i < n; i++) {
    if (a[i].start < lo) lo = a[i].start;
    if (a[i].end > hi) hi = a[i].end;
  }
  for (size_t t = lo; t < hi; t++) {
    size_t overlap = 0;
    for (size_t i = 0; i < n; i++)
      overlap += a[i].start <= t && t < a[i].end;
    if (overlap > best) best = overlap;
  }
  return best;
}
