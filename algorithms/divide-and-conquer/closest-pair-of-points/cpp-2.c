#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct { double x, y; } Point;
typedef struct { Point p, q; double dist; } Pair;

static int cmpX(const void *a, const void *b) {
  double d = ((const Point *)a)->x - ((const Point *)b)->x;
  return (d > 0) - (d < 0);
}

static double dist(Point a, Point b) { return hypot(a.x - b.x, a.y - b.y); }

static void update(Pair *best, Point a, Point b) {
  double d = dist(a, b);
  if (d < best->dist) *best = (Pair){a, b, d};
}

static void mergeByY(Point *p, size_t mid, size_t n, Point *buf) {
  size_t l = 0, r = mid, s = 0;
  while (l < mid && r < n) buf[s++] = p[l].y <= p[r].y ? p[l++] : p[r++];
  while (l < mid) buf[s++] = p[l++];
  while (r < n) buf[s++] = p[r++];
  memcpy(p, buf, n * sizeof *p);
}

static void rec(Point *p, size_t n, Point *buf, Pair *best) {
  if (n <= 3) {
    for (size_t i = 0; i < n; i++)
      for (size_t j = i + 1; j < n; j++) update(best, p[i], p[j]);
    for (size_t i = 1; i < n; i++)
      for (size_t j = i; j > 0 && p[j - 1].y > p[j].y; j--) {
        Point t = p[j]; p[j] = p[j - 1]; p[j - 1] = t;
      }
    return;
  }
  size_t mid = n / 2;
  double midX = p[mid].x;
  rec(p, mid, buf, best);
  rec(p + mid, n - mid, buf, best);
  mergeByY(p, mid, n, buf);

  size_t m = 0;
  for (size_t i = 0; i < n; i++) {
    if (fabs(p[i].x - midX) >= best->dist) continue;
    for (size_t j = m; j-- > 0 && p[i].y - buf[j].y < best->dist; )
      update(best, p[i], buf[j]);
    buf[m++] = p[i];
  }
}

Pair closestPair(const Point *pts, size_t n) {
  Pair best = {{0, 0}, {0, 0}, DBL_MAX};
  Point *p = malloc(n * sizeof *p), *buf = malloc(n * sizeof *buf);
  memcpy(p, pts, n * sizeof *p);
  qsort(p, n, sizeof *p, cmpX);
  rec(p, n, buf, &best);
  free(p);
  free(buf);
  return best;
}
