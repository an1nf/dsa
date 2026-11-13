#ifndef UNION_FIND_H
#define UNION_FIND_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
  size_t *parent, *rank, n;
} UnionFind;

UnionFind *ufNew(size_t n);
void ufFree(UnionFind *uf);
size_t ufFindSet(UnionFind *uf, size_t x);
void ufUnion(UnionFind *uf, size_t x, size_t y);
bool ufSameSet(UnionFind *uf, size_t x, size_t y);

#endif
