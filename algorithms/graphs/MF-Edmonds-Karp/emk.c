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

long edmondsKarp(size_t n, const Edge *e, size_t m, size_t s, size_t t, long *flow) {
  Net g = residualNetwork(n, e, m);
  size_t *via = malloc(n * sizeof *via), *queue = malloc(n * sizeof *queue);
  long total = 0;
  for (;;) {
    for (size_t v = 0; v < n; v++) via[v] = SIZE_MAX;
    size_t head = 0, tail = 0;
    queue[tail++] = s;
    while (head < tail && via[t] == SIZE_MAX) {
      size_t u = queue[head++];
      for (size_t k = g.start[u]; k < g.start[u + 1]; k++) {
        size_t a = g.arc[k], v = g.to[a];
        if (g.res[a] > 0 && v != s && via[v] == SIZE_MAX) {
          via[v] = a;
          queue[tail++] = v;
        }
      }
    }
    if (via[t] == SIZE_MAX) break;
    long b = LONG_MAX;
    for (size_t v = t; v != s; v = g.to[via[v] ^ 1])
      if (g.res[via[v]] < b) b = g.res[via[v]];
    for (size_t v = t; v != s; v = g.to[via[v] ^ 1]) {
      g.res[via[v]] -= b;
      g.res[via[v] ^ 1] += b;
    }
    total += b;
  }
  edgeFlows(&g, e, m, flow);
  free(via); free(queue); freeNetwork(&g);
  return total;
}
