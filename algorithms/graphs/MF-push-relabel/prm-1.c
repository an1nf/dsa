#include <stdbool.h>
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

long genericPushRelabel(size_t n, const Edge *e, size_t m, size_t s, size_t t, long *flow) {
  Net g = residualNetwork(n, e, m);
  size_t *h = calloc(n, sizeof *h), *queue = malloc((n + 1) * sizeof *queue);
  long *excess = calloc(n, sizeof *excess);
  bool *active = calloc(n, sizeof *active);
  size_t head = 0, tail = 0;
  h[s] = n;
  for (size_t k = g.start[s]; k < g.start[s + 1]; k++) {
    size_t a = g.arc[k], v = g.to[a];
    long c = g.res[a];
    g.res[a] -= c;
    g.res[a ^ 1] += c;
    excess[v] += c;
    excess[s] -= c;
    if (v != s && v != t && !active[v] && excess[v] > 0) {
      active[v] = true;
      queue[tail] = v; tail = (tail + 1) % (n + 1);
    }
  }
  while (head != tail) {
    size_t u = queue[head]; head = (head + 1) % (n + 1);
    while (excess[u] > 0) {
      size_t minH = SIZE_MAX;
      for (size_t k = g.start[u]; k < g.start[u + 1] && excess[u] > 0; k++) {
        size_t a = g.arc[k], v = g.to[a];
        if (g.res[a] <= 0) continue;
        if (h[u] == h[v] + 1) {
          long d = excess[u] < g.res[a] ? excess[u] : g.res[a];
          g.res[a] -= d;
          g.res[a ^ 1] += d;
          excess[u] -= d;
          excess[v] += d;
          if (v != s && v != t && !active[v]) {
            active[v] = true;
            queue[tail] = v; tail = (tail + 1) % (n + 1);
          }
        } else if (h[v] < minH) minH = h[v];
      }
      if (excess[u] > 0) h[u] = minH + 1;
    }
    active[u] = false;
  }
  long total = excess[t];
  edgeFlows(&g, e, m, flow);
  free(h); free(queue); free(excess); free(active); freeNetwork(&g);
  return total;
}
