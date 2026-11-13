#include <stdlib.h>

typedef struct { size_t start, end; } Activity;
typedef struct { size_t time, act; int isStart; } Event;

static int cmpEvents(const void *a, const void *b) {
  const Event *x = a, *y = b;
  if (x->time != y->time) return x->time < y->time ? -1 : 1;
  return x->isStart - y->isStart;
}

size_t scheduleHalls(const Activity *a, size_t n, size_t *hall) {
  Event *ev = malloc(2 * n * sizeof *ev);
  size_t *free_ = malloc(n * sizeof *free_), top = 0, halls = 0;
  for (size_t i = 0; i < n; i++) {
    ev[2 * i] = (Event){a[i].start, i, 1};
    ev[2 * i + 1] = (Event){a[i].end, i, 0};
  }
  qsort(ev, 2 * n, sizeof *ev, cmpEvents);
  for (size_t k = 0; k < 2 * n; k++) {
    size_t i = ev[k].act;
    if (ev[k].isStart) hall[i] = top ? free_[--top] : halls++;
    else free_[top++] = hall[i];
  }
  free(ev);
  free(free_);
  return halls;
}
