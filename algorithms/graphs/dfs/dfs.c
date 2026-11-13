#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct { size_t u, v; } Edge;
typedef enum { TREE, BACK, FORWARD, CROSS } EdgeType;
typedef enum { WHITE, GRAY, BLACK } Color;

typedef struct {
  const Edge *e;
  size_t *start, *adj, *d, *f, *parent, time;
  Color *color;
  EdgeType *type;
} Dfs;

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

static void dfsVisit(Dfs *g, size_t u) {
  g->d[u] = ++g->time;
  g->color[u] = GRAY;
  for (size_t k = g->start[u]; k < g->start[u + 1]; k++) {
    size_t i = g->adj[k], v = g->e[i].v;
    if (g->color[v] == WHITE) {
      g->type[i] = TREE;
      g->parent[v] = u;
      dfsVisit(g, v);
    } else if (g->color[v] == GRAY) g->type[i] = BACK;
    else g->type[i] = g->d[v] > g->d[u] ? FORWARD : CROSS;
  }
  g->f[u] = ++g->time;
  g->color[u] = BLACK;
}

void dfs(size_t n, const Edge *e, size_t m, size_t *d, size_t *f, size_t *parent,
         EdgeType *type) {
  Dfs g = {e, NULL, NULL, d, f, parent, 0, calloc(n, sizeof(Color)), type};
  g.adj = adjacency(n, e, m, &g.start);
  for (size_t v = 0; v < n; v++) parent[v] = SIZE_MAX;
  for (size_t v = 0; v < n; v++)
    if (g.color[v] == WHITE) dfsVisit(&g, v);
  free(g.start); free(g.adj); free(g.color);
}
