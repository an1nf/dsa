#include <stdlib.h>
#include "unionFind.h"

UnionFind *ufNew(size_t n) {
  UnionFind *uf = malloc(sizeof *uf);
  uf->n = n;
  uf->parent = malloc(n * sizeof *uf->parent);
  uf->rank = calloc(n, sizeof *uf->rank);
  for (size_t x = 0; x < n; x++) uf->parent[x] = x;
  return uf;
}

void ufFree(UnionFind *uf) {
  free(uf->parent);
  free(uf->rank);
  free(uf);
}

size_t ufFindSet(UnionFind *uf, size_t x) {
  if (uf->parent[x] != x) uf->parent[x] = ufFindSet(uf, uf->parent[x]);
  return uf->parent[x];
}

void ufUnion(UnionFind *uf, size_t x, size_t y) {
  x = ufFindSet(uf, x);
  y = ufFindSet(uf, y);
  if (x == y) return;
  if (uf->rank[x] < uf->rank[y]) { size_t t = x; x = y; y = t; }
  uf->parent[y] = x;
  if (uf->rank[x] == uf->rank[y]) uf->rank[x]++;
}

bool ufSameSet(UnionFind *uf, size_t x, size_t y) {
  return ufFindSet(uf, x) == ufFindSet(uf, y);
}
