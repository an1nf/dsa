#include <stdlib.h>
#include "dll.h"

List *listNew(void) {
  List *L = malloc(sizeof *L);
  L->nil.prev = L->nil.next = &L->nil;
  L->size = 0;
  return L;
}

void listFree(List *L) {
  for (Node *x = L->nil.next, *next; x != &L->nil; x = next) {
    next = x->next;
    free(x);
  }
  free(L);
}

Node *listSearch(List *L, int key) {
  Node *x = L->nil.next;
  while (x != &L->nil && x->key != key) x = x->next;
  return x == &L->nil ? NULL : x;
}

static Node *insertAfter(List *L, Node *y, int key) {
  Node *x = malloc(sizeof *x);
  x->key = key;
  x->next = y->next;
  x->prev = y;
  y->next->prev = x;
  y->next = x;
  L->size++;
  return x;
}

Node *listPrepend(List *L, int key) { return insertAfter(L, &L->nil, key); }

Node *listAppend(List *L, int key) { return insertAfter(L, L->nil.prev, key); }

void listDelete(List *L, Node *x) {
  x->prev->next = x->next;
  x->next->prev = x->prev;
  L->size--;
  free(x);
}
