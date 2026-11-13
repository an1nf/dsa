#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct { size_t u, v; } Edge;

static size_t *adjacency(size_t n, const Edge *e, size_t m, size_t **start) {
  size_t *s = calloc(n + 1, sizeof *s), *adj = malloc(m * sizeof *adj),
         *pos = malloc(n * sizeof *pos);
  for (size_t i = 0; i < m; i++) s[e[i].u + 1]++;
  for (size_t v = 0; v < n; v++) s[v + 1] += s[v];
  memcpy(pos, s, n * sizeof *pos);
  for (size_t i = 0; i < m; i++) adj[pos[e[i].u]++] = i;
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

void topologicalSort(size_t n, const Edge *e, size_t m, size_t *order) {
  size_t *start, *adj = adjacency(n, e, m, &start), k = n;
  bool *seen = calloc(n, sizeof *seen);
  for (size_t v = 0; v < n; v++)
    if (!seen[v]) visit(e, start, adj, seen, v, order, &k);
  free(start); free(adj); free(seen);
}
