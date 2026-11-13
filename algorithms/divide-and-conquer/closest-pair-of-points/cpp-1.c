#include <float.h>
#include <math.h>
#include <stddef.h>

typedef struct { double x, y; } Point;
typedef struct { Point p, q; double dist; } Pair;

Pair closestPair(const Point *pts, size_t n) {
  Pair best = {{0, 0}, {0, 0}, DBL_MAX};
  for (size_t i = 0; i < n; i++)
    for (size_t j = i + 1; j < n; j++) {
      double d = hypot(pts[i].x - pts[j].x, pts[i].y - pts[j].y);
      if (d < best.dist) best = (Pair){pts[i], pts[j], d};
    }
  return best;
}
