#include <float.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct { size_t l, r; double w; } WPair;
typedef struct { size_t to; long cap; double cost; } Arc;

static void addArc(Arc *a, size_t *k, size_t u, size_t v, double cost, size_t *from) {
  from[*k] = u; a[(*k)++] = (Arc){v, 1, cost};
  from[*k] = v; a[(*k)++] = (Arc){u, 0, -cost};
}

double minCostBipartiteMatching(size_t nl, size_t nr, const WPair *p, size_t m,
                                size_t *match, size_t *size) {
  size_t n = nl + nr + 2, s = n - 2, t = n - 1, na = 2 * (m + nl + nr), k = 0;
  Arc *a = malloc(na * sizeof *a);
  size_t *from = malloc(na * sizeof *from), *via = malloc(n * sizeof *via);
  double *dist = malloc(n * sizeof *dist), total = 0;
  for (size_t i = 0; i < m; i++) addArc(a, &k, p[i].l, nl + p[i].r, p[i].w, from);
  for (size_t l = 0; l < nl; l++) addArc(a, &k, s, l, 0, from);
  for (size_t r = 0; r < nr; r++) addArc(a, &k, nl + r, t, 0, from);

  *size = 0;
  for (;;) {
    for (size_t v = 0; v < n; v++) dist[v] = DBL_MAX;
    dist[s] = 0;
    for (bool changed = true; changed; ) {
      changed = false;
      for (size_t i = 0; i < na; i++)
        if (a[i].cap > 0 && dist[from[i]] != DBL_MAX &&
            dist[from[i]] + a[i].cost < dist[a[i].to] - 1e-12) {
          dist[a[i].to] = dist[from[i]] + a[i].cost;
          via[a[i].to] = i;
          changed = true;
        }
    }
    if (dist[t] == DBL_MAX) break;
    for (size_t v = t; v != s; v = from[via[v]]) {
      a[via[v]].cap--;
      a[via[v] ^ 1].cap++;
    }
    total += dist[t];
    ++*size;
  }
  for (size_t l = 0; l < nl; l++) match[l] = SIZE_MAX;
  for (size_t i = 0; i < m; i++)
    if (a[2 * i].cap == 0) match[p[i].l] = p[i].r;
  free(a); free(from); free(via); free(dist);
  return total;
}
