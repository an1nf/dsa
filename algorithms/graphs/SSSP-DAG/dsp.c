#include <float.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct { size_t u, v; double w; } Edge;

static size_t *adjacency(size_t n, const Edge *e, size_t m, int undirected, size_t **start) {
  size_t *s = calloc(n + 1, sizeof *s), *adj = malloc(2 * m * sizeof *adj),
         *pos = malloc(n * sizeof *pos);
  for (size_t i = 0; i < m; i++) {
    s[e[i].u + 1]++;
    if (undirected) s[e[i].v + 1]++;
  }
  for (size_t v = 0; v < n; v++) s[v + 1] += s[v];
  memcpy(pos, s, n * sizeof *pos);
  for (size_t i = 0; i < m; i++) {
    adj[pos[e[i].u]++] = i;
    if (undirected) adj[pos[e[i].v]++] = i;
  }
  free(pos);
  *start = s;
  return adj;
}

static void visit(const Edge *e, const size_t *start, const size_t *adj, bool *seen,
                  size_t u, size_t *order, size_t *k) {
  seen[u] = true;
  for (size_t j = start[u]; j < start[u + 1]; j++)
    if (!seen[e[adj[j]].v]) visit(e, start, adj, seen, e[adj[j]].v, order, k);
  order[--*k] = u;
}

void dagShortestPaths(size_t n, const Edge *e, size_t m, size_t src, double *dist,
                      size_t *parent) {
  size_t *start, *adj = adjacency(n, e, m, 0, &start), *order = malloc(n * sizeof *order), k = n;
  bool *seen = calloc(n, sizeof *seen);
  for (size_t v = 0; v < n; v++)
    if (!seen[v]) visit(e, start, adj, seen, v, order, &k);
  for (size_t v = 0; v < n; v++) {
    dist[v] = DBL_MAX;
    parent[v] = SIZE_MAX;
  }
  dist[src] = 0;
  for (size_t i = 0; i < n; i++) {
    size_t u = order[i];
    if (dist[u] == DBL_MAX) continue;
    for (size_t j = start[u]; j < start[u + 1]; j++) {
      const Edge *x = &e[adj[j]];
      if (dist[u] + x->w < dist[x->v]) {
        dist[x->v] = dist[u] + x->w;
        parent[x->v] = u;
      }
    }
  }
  free(start); free(adj); free(order); free(seen);
}
