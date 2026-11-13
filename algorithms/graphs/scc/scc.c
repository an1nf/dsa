#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct { size_t u, v; } Edge;

static size_t *adjacency(size_t n, const Edge *e, size_t m, int transpose, size_t **start) {
  size_t *s = calloc(n + 1, sizeof *s), *adj = malloc(m * sizeof *adj),
         *pos = malloc(n * sizeof *pos);
  for (size_t i = 0; i < m; i++) s[(transpose ? e[i].v : e[i].u) + 1]++;
  for (size_t v = 0; v < n; v++) s[v + 1] += s[v];
  memcpy(pos, s, n * sizeof *pos);
  for (size_t i = 0; i < m; i++)
    adj[pos[transpose ? e[i].v : e[i].u]++] = transpose ? e[i].u : e[i].v;
  free(pos);
  *start = s;
  return adj;
}

static void finishOrder(const size_t *start, const size_t *adj, size_t *comp,
                        size_t u, size_t *order, size_t *k) {
  comp[u] = 0;
  for (size_t j = start[u]; j < start[u + 1]; j++)
    if (comp[adj[j]] == SIZE_MAX) finishOrder(start, adj, comp, adj[j], order, k);
  order[--*k] = u;
}

static void assign(const size_t *start, const size_t *adj, size_t *comp, size_t u, size_t c) {
  comp[u] = c;
  for (size_t j = start[u]; j < start[u + 1]; j++)
    if (comp[adj[j]] == SIZE_MAX) assign(start, adj, comp, adj[j], c);
}

size_t stronglyConnectedComponents(size_t n, const Edge *e, size_t m, size_t *comp) {
  size_t *s, *adj = adjacency(n, e, m, 0, &s), *st, *adjT = adjacency(n, e, m, 1, &st);
  size_t *order = malloc(n * sizeof *order), k = n, count = 0;
  for (size_t v = 0; v < n; v++) comp[v] = SIZE_MAX;
  for (size_t v = 0; v < n; v++)
    if (comp[v] == SIZE_MAX) finishOrder(s, adj, comp, v, order, &k);
  for (size_t v = 0; v < n; v++) comp[v] = SIZE_MAX;
  for (size_t i = 0; i < n; i++)
    if (comp[order[i]] == SIZE_MAX) assign(st, adjT, comp, order[i], count++);
  free(s); free(adj); free(st); free(adjT); free(order);
  return count;
}
