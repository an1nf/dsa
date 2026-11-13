#include <stdlib.h>
#include <string.h>
#include "binheap.h"

#define PARENT(i) (((i) - 1) / 2)
#define LEFT(i) (2 * (i) + 1)
#define RIGHT(i) (2 * (i) + 2)

static void swap(int *x, int *y) { int t = *x; *x = *y; *y = t; }

MaxHeap *heapNew(size_t capacity) {
  MaxHeap *H = malloc(sizeof *H);
  H->capacity = capacity ? capacity : 1;
  H->a = malloc(H->capacity * sizeof *H->a);
  H->size = 0;
  return H;
}

MaxHeap *buildMaxHeap(const int *a, size_t n) {
  MaxHeap *H = heapNew(n);
  memcpy(H->a, a, n * sizeof *a);
  H->size = n;
  for (size_t i = n / 2; i--; ) maxHeapify(H, i);
  return H;
}

void heapFree(MaxHeap *H) {
  free(H->a);
  free(H);
}

void maxHeapify(MaxHeap *H, size_t i) {
  for (;;) {
    size_t l = LEFT(i), r = RIGHT(i), largest = i;
    if (l < H->size && H->a[l] > H->a[largest]) largest = l;
    if (r < H->size && H->a[r] > H->a[largest]) largest = r;
    if (largest == i) return;
    swap(&H->a[i], &H->a[largest]);
    i = largest;
  }
}

int heapMaximum(const MaxHeap *H) { return H->a[0]; }

int heapExtractMax(MaxHeap *H) {
  int max = H->a[0];
  H->a[0] = H->a[--H->size];
  maxHeapify(H, 0);
  return max;
}

void heapIncreaseKey(MaxHeap *H, size_t i, int key) {
  H->a[i] = key;
  for (; i > 0 && H->a[PARENT(i)] < H->a[i]; i = PARENT(i))
    swap(&H->a[i], &H->a[PARENT(i)]);
}

void maxHeapInsert(MaxHeap *H, int key) {
  if (H->size == H->capacity)
    H->a = realloc(H->a, (H->capacity *= 2) * sizeof *H->a);
  H->a[H->size++] = key;
  heapIncreaseKey(H, H->size - 1, key);
}
