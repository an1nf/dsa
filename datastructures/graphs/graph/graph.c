#include <stdlib.h>
#include "graph.h"

Graph *graphNew(size_t n, bool directed) {
  Graph *G = malloc(sizeof *G);
  G->n = n;
  G->directed = directed;
  G->adj = calloc(n, sizeof *G->adj);
  return G;
}

void graphFree(Graph *G) {
  for (size_t v = 0; v < G->n; v++) free(G->adj[v].edges);
  free(G->adj);
  free(G);
}

static void append(AdjList *L, size_t to, double w) {
  if (L->size == L->capacity) {
    L->capacity = L->capacity ? 2 * L->capacity : 4;
    L->edges = realloc(L->edges, L->capacity * sizeof *L->edges);
  }
  L->edges[L->size++] = (Edge){to, w};
}

static bool removeEdge(AdjList *L, size_t to) {
  for (size_t i = 0; i < L->size; i++)
    if (L->edges[i].to == to) {
      L->edges[i] = L->edges[--L->size];
      return true;
    }
  return false;
}

void graphAddEdge(Graph *G, size_t u, size_t v, double w) {
  append(&G->adj[u], v, w);
  if (!G->directed && u != v) append(&G->adj[v], u, w);
}

bool graphDelEdge(Graph *G, size_t u, size_t v) {
  bool found = removeEdge(&G->adj[u], v);
  if (found && !G->directed && u != v) removeEdge(&G->adj[v], u);
  return found;
}

Edge *graphGetEdge(const Graph *G, size_t u, size_t v) {
  for (size_t i = 0; i < G->adj[u].size; i++)
    if (G->adj[u].edges[i].to == v) return &G->adj[u].edges[i];
  return NULL;
}

Graph *graphTranspose(const Graph *G) {
  Graph *T = graphNew(G->n, G->directed);
  for (size_t u = 0; u < G->n; u++)
    for (size_t i = 0; i < G->adj[u].size; i++)
      append(&T->adj[G->adj[u].edges[i].to], u, G->adj[u].edges[i].w);
  return T;
}
