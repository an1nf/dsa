#include <stdlib.h>

typedef struct { size_t u, v; double w; } Edge;

static size_t findSet(size_t *p, size_t x) {
  while (p[x] != x) x = p[x] = p[p[x]];
  return x;
}

static int byWeight(const void *a, const void *b) {
  double d = ((const Edge *)a)->w - ((const Edge *)b)->w;
  return (d > 0) - (d < 0);
}

size_t kruskal(size_t n, Edge *e, size_t m, Edge *mst, double *total) {
  size_t *p = malloc(n * sizeof *p), *rank = calloc(n, sizeof *rank), k = 0;
  for (size_t v = 0; v < n; v++) p[v] = v;
  qsort(e, m, sizeof *e, byWeight);
  *total = 0;
  for (size_t i = 0; i < m && k + 1 < n; i++) {
    size_t a = findSet(p, e[i].u), b = findSet(p, e[i].v);
    if (a == b) continue;
    if (rank[a] < rank[b]) { size_t t = a; a = b; b = t; }
    p[b] = a;
    if (rank[a] == rank[b]) rank[a]++;
    mst[k++] = e[i];
    *total += e[i].w;
  }
  free(p);
  free(rank);
  return k;
}
