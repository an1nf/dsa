#include <float.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct { size_t u, v; double w; } Edge;

bool bellmanFord(size_t n, const Edge *e, size_t m, size_t src, double *dist, size_t *parent) {
  for (size_t v = 0; v < n; v++) {
    dist[v] = DBL_MAX;
    parent[v] = SIZE_MAX;
  }
  dist[src] = 0;
  for (size_t i = 1; i < n; i++)
    for (size_t j = 0; j < m; j++)
      if (dist[e[j].u] != DBL_MAX && dist[e[j].u] + e[j].w < dist[e[j].v]) {
        dist[e[j].v] = dist[e[j].u] + e[j].w;
        parent[e[j].v] = e[j].u;
      }
  for (size_t j = 0; j < m; j++)
    if (dist[e[j].u] != DBL_MAX && dist[e[j].u] + e[j].w < dist[e[j].v]) return false;
  return true;
}
