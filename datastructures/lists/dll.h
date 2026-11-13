#ifndef DLL_H
#define DLL_H

#include <stddef.h>

typedef struct Node {
  int key;
  struct Node *prev, *next;
} Node;

typedef struct {
  Node nil;
  size_t size;
} List;

List *listNew(void);
void listFree(List *L);
Node *listSearch(List *L, int key);
Node *listPrepend(List *L, int key);
Node *listAppend(List *L, int key);
void listDelete(List *L, Node *x);

#endif
