#ifndef BST_H
#define BST_H

#include <stddef.h>

typedef struct BstNode {
  int key;
  struct BstNode *left, *right, *p;
} BstNode;

typedef struct {
  BstNode *root;
  size_t size;
} Bst;

Bst *bstNew(void);
void bstFree(Bst *T);
BstNode *bstSearch(const Bst *T, int key);
BstNode *bstMinimum(BstNode *x);
BstNode *bstMaximum(BstNode *x);
BstNode *bstSuccessor(BstNode *x);
BstNode *bstPredecessor(BstNode *x);
BstNode *bstInsert(Bst *T, int key);
void bstDelete(Bst *T, BstNode *z);

#endif
