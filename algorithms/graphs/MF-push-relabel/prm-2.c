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

static void discharge(Net *g, size_t u, size_t *h, long *excess, size_t *current) {
  while (excess[u] > 0) {
    if (current[u] == g->start[u + 1]) {
      size_t minH = SIZE_MAX;
      for (size_t k = g->start[u]; k < g->start[u + 1]; k++)
        if (g->res[g->arc[k]] > 0 && h[g->to[g->arc[k]]] < minH) minH = h[g->to[g->arc[k]]];
      h[u] = minH + 1;
      current[u] = g->start[u];
      continue;
    }
    size_t a = g->arc[current[u]], v = g->to[a];
    if (g->res[a] > 0 && h[u] == h[v] + 1) {
      long d = excess[u] < g->res[a] ? excess[u] : g->res[a];
      g->res[a] -= d;
      g->res[a ^ 1] += d;
      excess[u] -= d;
      excess[v] += d;
    } else current[u]++;
  }
}

long relabelToFront(size_t n, const Edge *e, size_t m, size_t s, size_t t, long *flow) {
  Net g = residualNetwork(n, e, m);
  size_t *h = calloc(n, sizeof *h), *current = malloc(n * sizeof *current),
         *L = malloc(n * sizeof *L), len = 0;
  long *excess = calloc(n, sizeof *excess);
  h[s] = n;
  for (size_t k = g.start[s]; k < g.start[s + 1]; k++) {
    size_t a = g.arc[k];
    excess[g.to[a]] += g.res[a];
    excess[s] -= g.res[a];
    g.res[a ^ 1] += g.res[a];
    g.res[a] = 0;
  }
  for (size_t v = 0; v < n; v++) {
    current[v] = g.start[v];
    if (v != s && v != t) L[len++] = v;
  }
  for (size_t i = 0; i < len; ) {
    size_t u = L[i], old = h[u];
    discharge(&g, u, h, excess, current);
    if (h[u] > old) {
      memmove(L + 1, L, i * sizeof *L);
      L[0] = u;
      i = 1;
    } else i++;
  }
  long total = excess[t];
  edgeFlows(&g, e, m, flow);
  free(h); free(current); free(L); free(excess); freeNetwork(&g);
  return total;
}
