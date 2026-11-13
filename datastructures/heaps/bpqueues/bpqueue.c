#include <stdint.h>
#include <stdlib.h>
#include "bpqueue.h"

static void swapAt(MinPQ *pq, size_t i, size_t j) {
  size_t t = pq->heap[i]; pq->heap[i] = pq->heap[j]; pq->heap[j] = t;
  pq->pos[pq->heap[i]] = i;
  pq->pos[pq->heap[j]] = j;
}

static bool less(const MinPQ *pq, size_t i, size_t j) {
  return pq->key[pq->heap[i]] < pq->key[pq->heap[j]];
}

static void siftUp(MinPQ *pq, size_t i) {
  for (; i > 0 && less(pq, i, (i - 1) / 2); i = (i - 1) / 2) swapAt(pq, i, (i - 1) / 2);
}

static void siftDown(MinPQ *pq, size_t i) {
  for (;;) {
    size_t l = 2 * i + 1, r = l + 1, s = i;
    if (l < pq->size && less(pq, l, s)) s = l;
    if (r < pq->size && less(pq, r, s)) s = r;
    if (s == i) return;
    swapAt(pq, i, s);
    i = s;
  }
}

MinPQ *pqNew(size_t n) {
  MinPQ *pq = malloc(sizeof *pq);
  pq->n = n;
  pq->size = 0;
  pq->heap = malloc(n * sizeof *pq->heap);
  pq->pos = malloc(n * sizeof *pq->pos);
  pq->key = malloc(n * sizeof *pq->key);
  for (size_t i = 0; i < n; i++) pq->pos[i] = SIZE_MAX;
  return pq;
}

void pqFree(MinPQ *pq) {
  free(pq->heap); free(pq->pos); free(pq->key); free(pq);
}

bool pqIsEmpty(const MinPQ *pq) { return pq->size == 0; }

bool pqContains(const MinPQ *pq, size_t item) { return pq->pos[item] != SIZE_MAX; }

void pqInsert(MinPQ *pq, size_t item, double key) {
  pq->key[item] = key;
  pq->heap[pq->size] = item;
  pq->pos[item] = pq->size;
  siftUp(pq, pq->size++);
}

size_t pqMinimum(const MinPQ *pq) { return pq->heap[0]; }

size_t pqExtractMin(MinPQ *pq) {
  size_t min = pq->heap[0];
  pqDelete(pq, min);
  return min;
}

void pqDecreaseKey(MinPQ *pq, size_t item, double key) {
  pq->key[item] = key;
  siftUp(pq, pq->pos[item]);
}

void pqDelete(MinPQ *pq, size_t item) {
  size_t i = pq->pos[item];
  swapAt(pq, i, --pq->size);
  pq->pos[item] = SIZE_MAX;
  if (i < pq->size) {
    siftUp(pq, i);
    siftDown(pq, i);
  }
}
