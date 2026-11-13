#ifndef BINHEAP_H
#define BINHEAP_H

#include <stddef.h>

typedef struct {
  int *a;
  size_t size, capacity;
} MaxHeap;

MaxHeap *heapNew(size_t capacity);
MaxHeap *buildMaxHeap(const int *a, size_t n);
void heapFree(MaxHeap *H);
void maxHeapify(MaxHeap *H, size_t i);
int heapMaximum(const MaxHeap *H);
int heapExtractMax(MaxHeap *H);
void heapIncreaseKey(MaxHeap *H, size_t i, int key);
void maxHeapInsert(MaxHeap *H, int key);

#endif
