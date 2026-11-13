#include <stdlib.h>
#include "bst.h"

Bst *bstNew(void) {
  Bst *T = malloc(sizeof *T);
  T->root = NULL;
  T->size = 0;
  return T;
}

static void freeSubtree(BstNode *x) {
  if (!x) return;
  freeSubtree(x->left);
  freeSubtree(x->right);
  free(x);
}

void bstFree(Bst *T) {
  freeSubtree(T->root);
  free(T);
}

BstNode *bstSearch(const Bst *T, int key) {
  BstNode *x = T->root;
  while (x && key != x->key) x = key < x->key ? x->left : x->right;
  return x;
}

BstNode *bstMinimum(BstNode *x) {
  while (x->left) x = x->left;
  return x;
}

BstNode *bstMaximum(BstNode *x) {
  while (x->right) x = x->right;
  return x;
}

BstNode *bstSuccessor(BstNode *x) {
  if (x->right) return bstMinimum(x->right);
  BstNode *y = x->p;
  while (y && x == y->right) { x = y; y = y->p; }
  return y;
}

BstNode *bstPredecessor(BstNode *x) {
  if (x->left) return bstMaximum(x->left);
  BstNode *y = x->p;
  while (y && x == y->left) { x = y; y = y->p; }
  return y;
}

BstNode *bstInsert(Bst *T, int key) {
  BstNode *z = malloc(sizeof *z), *y = NULL, *x = T->root;
  *z = (BstNode){key, NULL, NULL, NULL};
  while (x) {
    y = x;
    x = key < x->key ? x->left : x->right;
  }
  z->p = y;
  if (!y) T->root = z;
  else if (key < y->key) y->left = z;
  else y->right = z;
  T->size++;
  return z;
}

static void transplant(Bst *T, BstNode *u, BstNode *v) {
  if (!u->p) T->root = v;
  else if (u == u->p->left) u->p->left = v;
  else u->p->right = v;
  if (v) v->p = u->p;
}

void bstDelete(Bst *T, BstNode *z) {
  if (!z->left) transplant(T, z, z->right);
  else if (!z->right) transplant(T, z, z->left);
  else {
    BstNode *y = bstMinimum(z->right);
    if (y != z->right) {
      transplant(T, y, y->right);
      y->right = z->right;
      y->right->p = y;
    }
    transplant(T, z, y);
    y->left = z->left;
    y->left->p = y;
  }
  T->size--;
  free(z);
}
