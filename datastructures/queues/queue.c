#include <stdlib.h>
#include "queue.h"

Queue *queueNew(size_t capacity) {
  Queue *Q = malloc(sizeof *Q);
  Q->capacity = capacity ? capacity : 1;
  Q->items = malloc(Q->capacity * sizeof *Q->items);
  Q->head = Q->size = 0;
  return Q;
}

void queueFree(Queue *Q) {
  free(Q->items);
  free(Q);
}

bool queueIsEmpty(const Queue *Q) { return Q->size == 0; }

void enqueue(Queue *Q, int x) {
  if (Q->size == Q->capacity) {
    int *items = malloc(2 * Q->capacity * sizeof *items);
    for (size_t i = 0; i < Q->size; i++)
      items[i] = Q->items[(Q->head + i) % Q->capacity];
    free(Q->items);
    Q->items = items;
    Q->head = 0;
    Q->capacity *= 2;
  }
  Q->items[(Q->head + Q->size++) % Q->capacity] = x;
}

int dequeue(Queue *Q) {
  int x = Q->items[Q->head];
  Q->head = (Q->head + 1) % Q->capacity;
  Q->size--;
  return x;
}

int queuePeek(const Queue *Q) { return Q->items[Q->head]; }
