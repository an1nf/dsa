#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
  int *items;
  size_t head, size, capacity;
} Queue;

Queue *queueNew(size_t capacity);
void queueFree(Queue *Q);
bool queueIsEmpty(const Queue *Q);
void enqueue(Queue *Q, int x);
int dequeue(Queue *Q);
int queuePeek(const Queue *Q);

#endif
