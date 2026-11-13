#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

typedef struct { size_t u, v; long cap; } Edge;
typedef struct { size_t n, *start, *arc, *to; long *res; } Net;

static Net residualNetwork(size_t n, const Edge *e, size_t m) {
  Net g = {n, calloc(n + 1, sizeof(size_t)), malloc(2 * m * sizeof(size_t)),
           malloc(2 * m * sizeof(size_t)), malloc(2 * m * sizeof(long))};
  size_t *pos = malloc(n * sizeof *pos);
  for (size_t i = 0; i < m; i++) {
    g.to[2 * i] = e[i].v; g.res[2 * i] = e[i].cap;
    g.to[2 * i + 1] = e[i].u; g.res[2 * i + 1] = 0;
    g.start[e[i].u + 1]++;
    g.start[e[i].v + 1]++;
  }
  for (size_t v = 0; v < n; v++) g.start[v + 1] += g.start[v];
  memcpy(pos, g.start, n * sizeof *pos);
  for (size_t i = 0; i < m; i++) {
    g.arc[pos[e[i].u]++] = 2 * i;
    g.arc[pos[e[i].v]++] = 2 * i + 1;
  }
  free(pos);
  return g;
}

static void edgeFlows(const Net *g, const Edge *e, size_t m, long *flow) {
  if (flow)
    for (size_t i = 0; i < m; i++) flow[i] = e[i].cap - g->res[2 * i];
}

static void freeNetwork(Net *g) {
  free(g->start); free(g->arc); free(g->to); free(g->res);
}

static long augment(Net *g, bool *seen, size_t u, size_t t, long limit, long delta) {
  if (u == t) return limit;
  seen[u] = true;
  for (size_t k = g->start[u]; k < g->start[u + 1]; k++) {
    size_t a = g->arc[k];
    if (g->res[a] >= delta && !seen[g->to[a]]) {
      long b = augment(g, seen, g->to[a], t, limit < g->res[a] ? limit : g->res[a], delta);
      if (b > 0) {
        g->res[a] -= b;
        g->res[a ^ 1] += b;
        return b;
      }
    }
  }
  return 0;
}

long capacityScaling(size_t n, const Edge *e, size_t m, size_t s, size_t t, long *flow) {
  Net g = residualNetwork(n, e, m);
  bool *seen = malloc(n * sizeof *seen);
  long maxCap = 0, total = 0, b;
  for (size_t i = 0; i < m; i++)
    if (e[i].cap > maxCap) maxCap = e[i].cap;
  long delta = 1;
  while (delta * 2 <= maxCap) delta *= 2;
  for (; delta >= 1; delta /= 2)
    do {
      memset(seen, 0, n * sizeof *seen);
      total += b = augment(&g, seen, s, t, LONG_MAX, delta);
    } while (b > 0);
  edgeFlows(&g, e, m, flow);
  free(seen); freeNetwork(&g);
  return total;
}
