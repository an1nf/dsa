#include <math.h>
#include <stdlib.h>
#include "graph.h"

Graph *graphNew(size_t n, bool directed) {
  Graph *G = malloc(sizeof *G);
  G->n = n;
  G->directed = directed;
  G->w = malloc(n * n * sizeof *G->w);
  for (size_t i = 0; i < n * n; i++) G->w[i] = INFINITY;
  return G;
}

void graphFree(Graph *G) {
  free(G->w);
  free(G);
}

void graphAddEdge(Graph *G, size_t u, size_t v, double w) {
  G->w[u * G->n + v] = w;
  if (!G->directed) G->w[v * G->n + u] = w;
}

void graphDelEdge(Graph *G, size_t u, size_t v) {
  G->w[u * G->n + v] = INFINITY;
  if (!G->directed) G->w[v * G->n + u] = INFINITY;
}

bool graphHasEdge(const Graph *G, size_t u, size_t v) { return !isinf(G->w[u * G->n + v]); }

double graphWeight(const Graph *G, size_t u, size_t v) { return G->w[u * G->n + v]; }

Graph *graphTranspose(const Graph *G) {
  Graph *T = graphNew(G->n, G->directed);
  for (size_t u = 0; u < G->n; u++)
    for (size_t v = 0; v < G->n; v++) T->w[v * G->n + u] = G->w[u * G->n + v];
  return T;
}
