#ifndef NETWORK_H
#define NETWORK_H

#include <stddef.h>

typedef struct {
  size_t from, to;
  long cap, flow;
} Arc;

typedef struct {
  size_t *arcs, size, capacity;
} ArcList;

typedef struct {
  size_t n, m, arcCapacity;
  Arc *arcs;
  ArcList *out;
} Network;

Network *networkNew(size_t n);
void networkFree(Network *N);
size_t networkAddEdge(Network *N, size_t u, size_t v, long cap);
long residualCapacity(const Network *N, size_t a);
void pushFlow(Network *N, size_t a, long delta);
long flowValue(const Network *N, size_t s);

#endif
