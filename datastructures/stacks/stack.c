#include <stdlib.h>
#include "stack.h"

Stack *stackNew(size_t capacity) {
  Stack *S = malloc(sizeof *S);
  S->capacity = capacity ? capacity : 1;
  S->items = malloc(S->capacity * sizeof *S->items);
  S->top = 0;
  return S;
}

void stackFree(Stack *S) {
  free(S->items);
  free(S);
}

bool stackIsEmpty(const Stack *S) { return S->top == 0; }

void stackPush(Stack *S, int x) {
  if (S->top == S->capacity)
    S->items = realloc(S->items, (S->capacity *= 2) * sizeof *S->items);
  S->items[S->top++] = x;
}

int stackPop(Stack *S) { return S->items[--S->top]; }

int stackTop(const Stack *S) { return S->items[S->top - 1]; }
