#include <stdint.h>
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

void bfs(size_t n, const Edge *e, size_t m, size_t src, size_t *dist, size_t *parent) {
  size_t *start, *adj = adjacency(n, e, m, &start), *queue = malloc(n * sizeof *queue);
  for (size_t v = 0; v < n; v++) dist[v] = parent[v] = SIZE_MAX;
  size_t head = 0, tail = 0;
  dist[src] = 0;
  queue[tail++] = src;
  while (head < tail) {
    size_t u = queue[head++];
    for (size_t k = start[u]; k < start[u + 1]; k++) {
      size_t v = e[adj[k]].v;
      if (dist[v] == SIZE_MAX) {
        dist[v] = dist[u] + 1;
        parent[v] = u;
        queue[tail++] = v;
      }
    }
  }
  free(start); free(adj); free(queue);
}
