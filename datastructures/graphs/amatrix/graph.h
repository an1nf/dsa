#ifndef AMATRIX_GRAPH_H
#define AMATRIX_GRAPH_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
  size_t n;
  bool directed;
  double *w;
} Graph;

Graph *graphNew(size_t n, bool directed);
void graphFree(Graph *G);
void graphAddEdge(Graph *G, size_t u, size_t v, double w);
void graphDelEdge(Graph *G, size_t u, size_t v);
bool graphHasEdge(const Graph *G, size_t u, size_t v);
double graphWeight(const Graph *G, size_t u, size_t v);
Graph *graphTranspose(const Graph *G);

#endif
