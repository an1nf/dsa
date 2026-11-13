#include <stdlib.h>
#include "network.h"

Network *networkNew(size_t n) {
  Network *N = malloc(sizeof *N);
  N->n = n;
  N->m = 0;
  N->arcCapacity = 8;
  N->arcs = malloc(N->arcCapacity * sizeof *N->arcs);
  N->out = calloc(n, sizeof *N->out);
  return N;
}

void networkFree(Network *N) {
  for (size_t v = 0; v < N->n; v++) free(N->out[v].arcs);
  free(N->out);
  free(N->arcs);
  free(N);
}

static void addArc(Network *N, size_t u, size_t v, long cap) {
  if (N->m == N->arcCapacity)
    N->arcs = realloc(N->arcs, (N->arcCapacity *= 2) * sizeof *N->arcs);
  N->arcs[N->m] = (Arc){u, v, cap, 0};
  ArcList *L = &N->out[u];
  if (L->size == L->capacity) {
    L->capacity = L->capacity ? 2 * L->capacity : 4;
    L->arcs = realloc(L->arcs, L->capacity * sizeof *L->arcs);
  }
  L->arcs[L->size++] = N->m++;
}

size_t networkAddEdge(Network *N, size_t u, size_t v, long cap) {
  addArc(N, u, v, cap);
  addArc(N, v, u, 0);
  return N->m - 2;
}

long residualCapacity(const Network *N, size_t a) { return N->arcs[a].cap - N->arcs[a].flow; }

void pushFlow(Network *N, size_t a, long delta) {
  N->arcs[a].flow += delta;
  N->arcs[a ^ 1].flow -= delta;
}

long flowValue(const Network *N, size_t s) {
  long f = 0;
  for (size_t i = 0; i < N->out[s].size; i++) f += N->arcs[N->out[s].arcs[i]].flow;
  return f;
}
