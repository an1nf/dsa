#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
  int *items;
  size_t top, capacity;
} Stack;

Stack *stackNew(size_t capacity);
void stackFree(Stack *S);
bool stackIsEmpty(const Stack *S);
void stackPush(Stack *S, int x);
int stackPop(Stack *S);
int stackTop(const Stack *S);

#endif
