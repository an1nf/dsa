#ifndef RBT_H
#define RBT_H

#include <stddef.h>

typedef enum { RED, BLACK } Color;

typedef struct RbNode {
  int key;
  Color color;
  struct RbNode *left, *right, *p;
} RbNode;

typedef struct {
  RbNode *root, nil;
  size_t size;
} Rbt;

Rbt *rbtNew(void);
void rbtFree(Rbt *T);
RbNode *rbtSearch(Rbt *T, int key);
RbNode *rbtMinimum(Rbt *T, RbNode *x);
RbNode *rbtMaximum(Rbt *T, RbNode *x);
RbNode *rbtSuccessor(Rbt *T, RbNode *x);
RbNode *rbtPredecessor(Rbt *T, RbNode *x);
RbNode *rbtInsert(Rbt *T, int key);
void rbtDelete(Rbt *T, RbNode *z);

#endif
