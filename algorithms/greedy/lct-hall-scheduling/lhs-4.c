#include <stdlib.h>

typedef struct { size_t start, end; } Activity;
typedef struct { size_t end, id; } Hall;

static const Activity *base;

static int byStart(const void *a, const void *b) {
  size_t x = base[*(const size_t *)a].start, y = base[*(const size_t *)b].start;
  return (x > y) - (x < y);
}

static void siftDown(Hall *h, size_t n, size_t i) {
  for (;;) {
    size_t l = 2 * i + 1, r = l + 1, m = i;
    if (l < n && h[l].end < h[m].end) m = l;
    if (r < n && h[r].end < h[m].end) m = r;
    if (m == i) return;
    Hall t = h[i]; h[i] = h[m]; h[m] = t;
    i = m;
  }
}

static void siftUp(Hall *h, size_t i) {
  for (; i > 0 && h[(i - 1) / 2].end > h[i].end; i = (i - 1) / 2) {
    Hall t = h[i]; h[i] = h[(i - 1) / 2]; h[(i - 1) / 2] = t;
  }
}

size_t scheduleHalls(const Activity *a, size_t n, size_t *hall) {
  size_t *order = malloc(n * sizeof *order), halls = 0;
  Hall *heap = malloc(n * sizeof *heap);
  for (size_t i = 0; i < n; i++) order[i] = i;
  base = a;
  qsort(order, n, sizeof *order, byStart);
  for (size_t k = 0; k < n; k++) {
    size_t i = order[k];
    if (halls > 0 && heap[0].end <= a[i].start) {
      hall[i] = heap[0].id;
      heap[0].end = a[i].end;
      siftDown(heap, halls, 0);
    } else {
      hall[i] = halls;
      heap[halls] = (Hall){a[i].end, halls};
      siftUp(heap, halls++);
    }
  }
  free(order);
  free(heap);
  return halls;
}
