#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
  size_t to;
  double w;
} Edge;

typedef struct {
  Edge *edges;
  size_t size, capacity;
} AdjList;

typedef struct {
  size_t n;
  bool directed;
  AdjList *adj;
} Graph;

Graph *graphNew(size_t n, bool directed);
void graphFree(Graph *G);
void graphAddEdge(Graph *G, size_t u, size_t v, double w);
bool graphDelEdge(Graph *G, size_t u, size_t v);
Edge *graphGetEdge(const Graph *G, size_t u, size_t v);
Graph *graphTranspose(const Graph *G);

#endif
