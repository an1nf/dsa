#include <stddef.h>

typedef struct { size_t start, end; } Activity;

size_t minHalls(const Activity *a, size_t n) {
  size_t best = 0;
  for (size_t i = 0; i < n; i++) {
    size_t overlap = 0;
    for (size_t j = 0; j < n; j++)
      overlap += a[j].start <= a[i].start && a[i].start < a[j].end;
    if (overlap > best) best = overlap;
  }
  return best;
}
