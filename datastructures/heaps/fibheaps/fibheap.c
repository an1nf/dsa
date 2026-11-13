#include <limits.h>
#include <stdlib.h>
#include "fibheap.h"

static void listInsert(FibNode *a, FibNode *x) {
  x->right = a->right;
  x->left = a;
  a->right->left = x;
  a->right = x;
}

static void listRemove(FibNode *x) {
  x->left->right = x->right;
  x->right->left = x->left;
  x->left = x->right = x;
}

static void addRoot(FibHeap *H, FibNode *x) {
  x->p = NULL;
  if (!H->min) {
    x->left = x->right = x;
    H->min = x;
  } else {
    listInsert(H->min, x);
    if (x->key < H->min->key) H->min = x;
  }
}

FibHeap *fibNew(void) {
  FibHeap *H = malloc(sizeof *H);
  H->min = NULL;
  H->n = 0;
  return H;
}

static void freeList(FibNode *x) {
  if (!x) return;
  FibNode *y = x;
  do {
    FibNode *next = y->right;
    freeList(y->child);
    free(y);
    y = next;
  } while (y != x);
}

void fibFree(FibHeap *H) {
  freeList(H->min);
  free(H);
}

FibNode *fibInsert(FibHeap *H, int key) {
  FibNode *x = malloc(sizeof *x);
  *x = (FibNode){key, 0, false, NULL, NULL, x, x};
  addRoot(H, x);
  H->n++;
  return x;
}

FibNode *fibMinimum(const FibHeap *H) { return H->min; }

FibHeap *fibUnion(FibHeap *H1, FibHeap *H2) {
  if (!H1->min) H1->min = H2->min;
  else if (H2->min) {
    FibNode *a = H1->min->right, *b = H2->min->left;
    H1->min->right = H2->min;
    H2->min->left = H1->min;
    a->left = b;
    b->right = a;
    if (H2->min->key < H1->min->key) H1->min = H2->min;
  }
  H1->n += H2->n;
  free(H2);
  return H1;
}

static void link(FibNode *y, FibNode *x) {
  listRemove(y);
  y->p = x;
  y->mark = false;
  if (!x->child) x->child = y;
  else listInsert(x->child, y);
  x->degree++;
}

static void consolidate(FibHeap *H) {
  FibNode *A[64] = {NULL}, **roots = malloc(H->n * sizeof *roots);
  size_t r = 0;
  FibNode *w = H->min;
  do { roots[r++] = w; w = w->right; } while (w != H->min);
  for (size_t i = 0; i < r; i++) {
    FibNode *x = roots[i];
    size_t d = x->degree;
    while (A[d]) {
      FibNode *y = A[d];
      if (y->key < x->key) { FibNode *t = x; x = y; y = t; }
      link(y, x);
      A[d++] = NULL;
    }
    A[d] = x;
  }
  free(roots);
  H->min = NULL;
  for (size_t d = 0; d < 64; d++)
    if (A[d]) {
      A[d]->left = A[d]->right = A[d];
      addRoot(H, A[d]);
    }
}

int fibExtractMin(FibHeap *H) {
  FibNode *z = H->min;
  int key = z->key;
  while (z->child) {
    FibNode *c = z->child;
    z->child = c->right == c ? NULL : c->right;
    listRemove(c);
    addRoot(H, c);
  }
  if (z->right == z) H->min = NULL;
  else {
    H->min = z->right;
    listRemove(z);
    consolidate(H);
  }
  H->n--;
  free(z);
  return key;
}

static void cut(FibHeap *H, FibNode *x, FibNode *y) {
  if (y->child == x) y->child = x->right == x ? NULL : x->right;
  listRemove(x);
  y->degree--;
  x->mark = false;
  addRoot(H, x);
}

static void cascadingCut(FibHeap *H, FibNode *y) {
  for (FibNode *z; (z = y->p); y = z) {
    if (!y->mark) {
      y->mark = true;
      return;
    }
    cut(H, y, z);
  }
}

void fibDecreaseKey(FibHeap *H, FibNode *x, int key) {
  x->key = key;
  FibNode *y = x->p;
  if (y && x->key < y->key) {
    cut(H, x, y);
    cascadingCut(H, y);
  }
  if (x->key < H->min->key) H->min = x;
}

void fibDelete(FibHeap *H, FibNode *x) {
  fibDecreaseKey(H, x, INT_MIN);
  H->min = x;
  fibExtractMin(H);
}
