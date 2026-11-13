#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct { size_t l, r; } Pair;

typedef struct {
  size_t nl, nr, *start, *adj, *matchL, *matchR, *dist;
} HK;

static bool bfs(HK *g, size_t *queue) {
  size_t head = 0, tail = 0;
  bool found = false;
  for (size_t l = 0; l < g->nl; l++) {
    g->dist[l] = g->matchL[l] == SIZE_MAX ? 0 : SIZE_MAX;
    if (g->dist[l] == 0) queue[tail++] = l;
  }
  while (head < tail) {
    size_t l = queue[head++];
    for (size_t k = g->start[l]; k < g->start[l + 1]; k++) {
      size_t l2 = g->matchR[g->adj[k]];
      if (l2 == SIZE_MAX) found = true;
      else if (g->dist[l2] == SIZE_MAX) {
        g->dist[l2] = g->dist[l] + 1;
        queue[tail++] = l2;
      }
    }
  }
  return found;
}

static bool dfs(HK *g, size_t l) {
  for (size_t k = g->start[l]; k < g->start[l + 1]; k++) {
    size_t r = g->adj[k], l2 = g->matchR[r];
    if (l2 == SIZE_MAX || (g->dist[l2] == g->dist[l] + 1 && dfs(g, l2))) {
      g->matchL[l] = r;
      g->matchR[r] = l;
      return true;
    }
  }
  g->dist[l] = SIZE_MAX;
  return false;
}

size_t hopcroftKarp(size_t nl, size_t nr, const Pair *p, size_t m, size_t *match) {
  HK g = {nl, nr, calloc(nl + 1, sizeof(size_t)), malloc(m * sizeof(size_t)), match,
          malloc(nr * sizeof(size_t)), malloc(nl * sizeof(size_t))};
  size_t *pos = malloc(nl * sizeof *pos), *queue = malloc(nl * sizeof *queue), size = 0;
  for (size_t i = 0; i < m; i++) g.start[p[i].l + 1]++;
  for (size_t l = 0; l < nl; l++) g.start[l + 1] += g.start[l];
  memcpy(pos, g.start, nl * sizeof *pos);
  for (size_t i = 0; i < m; i++) g.adj[pos[p[i].l]++] = p[i].r;
  for (size_t l = 0; l < nl; l++) match[l] = SIZE_MAX;
  for (size_t r = 0; r < nr; r++) g.matchR[r] = SIZE_MAX;
  while (bfs(&g, queue))
    for (size_t l = 0; l < nl; l++)
      if (match[l] == SIZE_MAX && dfs(&g, l)) size++;
  free(g.start); free(g.adj); free(g.matchR); free(g.dist); free(pos); free(queue);
  return size;
}
