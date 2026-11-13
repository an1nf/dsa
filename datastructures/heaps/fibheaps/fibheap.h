#ifndef FIBHEAP_H
#define FIBHEAP_H

#include <stdbool.h>
#include <stddef.h>

typedef struct FibNode {
  int key;
  size_t degree;
  bool mark;
  struct FibNode *p, *child, *left, *right;
} FibNode;

typedef struct {
  FibNode *min;
  size_t n;
} FibHeap;

FibHeap *fibNew(void);
void fibFree(FibHeap *H);
FibNode *fibInsert(FibHeap *H, int key);
FibNode *fibMinimum(const FibHeap *H);
FibHeap *fibUnion(FibHeap *H1, FibHeap *H2);
int fibExtractMin(FibHeap *H);
void fibDecreaseKey(FibHeap *H, FibNode *x, int key);
void fibDelete(FibHeap *H, FibNode *x);

#endif
