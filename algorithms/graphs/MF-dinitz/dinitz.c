#include <stdbool.h>
#include <limits.h>
#include <stdint.h>
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

static bool buildLevels(const Net *g, size_t s, size_t t, size_t *level, size_t *queue) {
  for (size_t v = 0; v < g->n; v++) level[v] = SIZE_MAX;
  size_t head = 0, tail = 0;
  level[s] = 0;
  queue[tail++] = s;
  while (head < tail) {
    size_t u = queue[head++];
    for (size_t k = g->start[u]; k < g->start[u + 1]; k++) {
      size_t a = g->arc[k];
      if (g->res[a] > 0 && level[g->to[a]] == SIZE_MAX) {
        level[g->to[a]] = level[u] + 1;
        queue[tail++] = g->to[a];
      }
    }
  }
  return level[t] != SIZE_MAX;
}

static long blockingPath(Net *g, const size_t *level, size_t *it, size_t u, size_t t, long limit) {
  if (u == t) return limit;
  for (; it[u] < g->start[u + 1]; it[u]++) {
    size_t a = g->arc[it[u]], v = g->to[a];
    if (g->res[a] > 0 && level[v] == level[u] + 1) {
      long b = blockingPath(g, level, it, v, t, limit < g->res[a] ? limit : g->res[a]);
      if (b > 0) {
        g->res[a] -= b;
        g->res[a ^ 1] += b;
        return b;
      }
    }
  }
  return 0;
}

long dinic(size_t n, const Edge *e, size_t m, size_t s, size_t t, long *flow) {
  Net g = residualNetwork(n, e, m);
  size_t *level = malloc(n * sizeof *level), *it = malloc(n * sizeof *it),
         *queue = malloc(n * sizeof *queue);
  long total = 0, b;
  while (buildLevels(&g, s, t, level, queue)) {
    memcpy(it, g.start, n * sizeof *it);
    while ((b = blockingPath(&g, level, it, s, t, LONG_MAX)) > 0) total += b;
  }
  edgeFlows(&g, e, m, flow);
  free(level); free(it); free(queue); freeNetwork(&g);
  return total;
}
