#ifndef BPQUEUE_H
#define BPQUEUE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
  size_t *heap, *pos, size, n;
  double *key;
} MinPQ;

MinPQ *pqNew(size_t n);
void pqFree(MinPQ *pq);
bool pqIsEmpty(const MinPQ *pq);
bool pqContains(const MinPQ *pq, size_t item);
void pqInsert(MinPQ *pq, size_t item, double key);
size_t pqMinimum(const MinPQ *pq);
size_t pqExtractMin(MinPQ *pq);
void pqDecreaseKey(MinPQ *pq, size_t item, double key);
void pqDelete(MinPQ *pq, size_t item);

#endif
