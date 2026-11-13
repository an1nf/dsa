#include <stdlib.h>
#include "rbt.h"

#define NIL (&T->nil)

Rbt *rbtNew(void) {
  Rbt *T = malloc(sizeof *T);
  T->nil = (RbNode){0, BLACK, NIL, NIL, NIL};
  T->root = NIL;
  T->size = 0;
  return T;
}

static void freeSubtree(Rbt *T, RbNode *x) {
  if (x == NIL) return;
  freeSubtree(T, x->left);
  freeSubtree(T, x->right);
  free(x);
}

void rbtFree(Rbt *T) {
  freeSubtree(T, T->root);
  free(T);
}

RbNode *rbtSearch(Rbt *T, int key) {
  RbNode *x = T->root;
  while (x != NIL && key != x->key) x = key < x->key ? x->left : x->right;
  return x == NIL ? NULL : x;
}

RbNode *rbtMinimum(Rbt *T, RbNode *x) {
  while (x->left != NIL) x = x->left;
  return x;
}

RbNode *rbtMaximum(Rbt *T, RbNode *x) {
  while (x->right != NIL) x = x->right;
  return x;
}

RbNode *rbtSuccessor(Rbt *T, RbNode *x) {
  if (x->right != NIL) return rbtMinimum(T, x->right);
  RbNode *y = x->p;
  while (y != NIL && x == y->right) { x = y; y = y->p; }
  return y == NIL ? NULL : y;
}

RbNode *rbtPredecessor(Rbt *T, RbNode *x) {
  if (x->left != NIL) return rbtMaximum(T, x->left);
  RbNode *y = x->p;
  while (y != NIL && x == y->left) { x = y; y = y->p; }
  return y == NIL ? NULL : y;
}

static void leftRotate(Rbt *T, RbNode *x) {
  RbNode *y = x->right;
  x->right = y->left;
  if (y->left != NIL) y->left->p = x;
  y->p = x->p;
  if (x->p == NIL) T->root = y;
  else if (x == x->p->left) x->p->left = y;
  else x->p->right = y;
  y->left = x;
  x->p = y;
}

static void rightRotate(Rbt *T, RbNode *x) {
  RbNode *y = x->left;
  x->left = y->right;
  if (y->right != NIL) y->right->p = x;
  y->p = x->p;
  if (x->p == NIL) T->root = y;
  else if (x == x->p->right) x->p->right = y;
  else x->p->left = y;
  y->right = x;
  x->p = y;
}

static void insertFixup(Rbt *T, RbNode *z) {
  while (z->p->color == RED) {
    RbNode *g = z->p->p;
    if (z->p == g->left) {
      RbNode *y = g->right;
      if (y->color == RED) {
        z->p->color = y->color = BLACK;
        g->color = RED;
        z = g;
      } else {
        if (z == z->p->right) { z = z->p; leftRotate(T, z); }
        z->p->color = BLACK;
        z->p->p->color = RED;
        rightRotate(T, z->p->p);
      }
    } else {
      RbNode *y = g->left;
      if (y->color == RED) {
        z->p->color = y->color = BLACK;
        g->color = RED;
        z = g;
      } else {
        if (z == z->p->left) { z = z->p; rightRotate(T, z); }
        z->p->color = BLACK;
        z->p->p->color = RED;
        leftRotate(T, z->p->p);
      }
    }
  }
  T->root->color = BLACK;
}

RbNode *rbtInsert(Rbt *T, int key) {
  RbNode *z = malloc(sizeof *z), *y = NIL, *x = T->root;
  while (x != NIL) {
    y = x;
    x = key < x->key ? x->left : x->right;
  }
  *z = (RbNode){key, RED, NIL, NIL, y};
  if (y == NIL) T->root = z;
  else if (key < y->key) y->left = z;
  else y->right = z;
  insertFixup(T, z);
  T->size++;
  return z;
}

static void transplant(Rbt *T, RbNode *u, RbNode *v) {
  if (u->p == NIL) T->root = v;
  else if (u == u->p->left) u->p->left = v;
  else u->p->right = v;
  v->p = u->p;
}

static void deleteFixup(Rbt *T, RbNode *x) {
  while (x != T->root && x->color == BLACK) {
    if (x == x->p->left) {
      RbNode *w = x->p->right;
      if (w->color == RED) {
        w->color = BLACK;
        x->p->color = RED;
        leftRotate(T, x->p);
        w = x->p->right;
      }
      if (w->left->color == BLACK && w->right->color == BLACK) {
        w->color = RED;
        x = x->p;
      } else {
        if (w->right->color == BLACK) {
          w->left->color = BLACK;
          w->color = RED;
          rightRotate(T, w);
          w = x->p->right;
        }
        w->color = x->p->color;
        x->p->color = BLACK;
        w->right->color = BLACK;
        leftRotate(T, x->p);
        x = T->root;
      }
    } else {
      RbNode *w = x->p->left;
      if (w->color == RED) {
        w->color = BLACK;
        x->p->color = RED;
        rightRotate(T, x->p);
        w = x->p->left;
      }
      if (w->right->color == BLACK && w->left->color == BLACK) {
        w->color = RED;
        x = x->p;
      } else {
        if (w->left->color == BLACK) {
          w->right->color = BLACK;
          w->color = RED;
          leftRotate(T, w);
          w = x->p->left;
        }
        w->color = x->p->color;
        x->p->color = BLACK;
        w->left->color = BLACK;
        rightRotate(T, x->p);
        x = T->root;
      }
    }
  }
  x->color = BLACK;
}

void rbtDelete(Rbt *T, RbNode *z) {
  RbNode *y = z, *x;
  Color yOriginal = y->color;
  if (z->left == NIL) {
    x = z->right;
    transplant(T, z, z->right);
  } else if (z->right == NIL) {
    x = z->left;
    transplant(T, z, z->left);
  } else {
    y = rbtMinimum(T, z->right);
    yOriginal = y->color;
    x = y->right;
    if (y != z->right) {
      transplant(T, y, y->right);
      y->right = z->right;
      y->right->p = y;
    } else x->p = y;
    transplant(T, z, y);
    y->left = z->left;
    y->left->p = y;
    y->color = z->color;
  }
  if (yOriginal == BLACK) deleteFixup(T, x);
  T->size--;
  free(z);
}
