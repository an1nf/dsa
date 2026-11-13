#include <float.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct { size_t u, v; double w; } Edge;

static size_t *adjacency(size_t n, const Edge *e, size_t m, int undirected, size_t **start) {
  size_t *s = calloc(n + 1, sizeof *s), *adj = malloc(2 * m * sizeof *adj),
         *pos = malloc(n * sizeof *pos);
  for (size_t i = 0; i < m; i++) {
    s[e[i].u + 1]++;
    if (undirected) s[e[i].v + 1]++;
  }
  for (size_t v = 0; v < n; v++) s[v + 1] += s[v];
  memcpy(pos, s, n * sizeof *pos);
  for (size_t i = 0; i < m; i++) {
    adj[pos[e[i].u]++] = i;
    if (undirected) adj[pos[e[i].v]++] = i;
  }
  free(pos);
  *start = s;
  return adj;
}

#define NIL SIZE_MAX

typedef struct { size_t parent, child, left, right, degree; bool mark, inHeap; } FibNode;
typedef struct { FibNode *x; double *key; size_t min, n; } FibHeap;

static void spliceIntoRoots(FibHeap *H, size_t v) {
  FibNode *x = H->x;
  x[v].parent = NIL;
  if (H->min == NIL) {
    x[v].left = x[v].right = v;
    H->min = v;
    return;
  }
  x[v].right = x[H->min].right;
  x[v].left = H->min;
  x[x[H->min].right].left = v;
  x[H->min].right = v;
  if (H->key[v] < H->key[H->min]) H->min = v;
}

static void unlink_(FibNode *x, size_t v) {
  x[x[v].left].right = x[v].right;
  x[x[v].right].left = x[v].left;
}

static void fibInsert(FibHeap *H, size_t v) {
  H->x[v] = (FibNode){NIL, NIL, v, v, 0, false, true};
  spliceIntoRoots(H, v);
  H->n++;
}

static void link_(FibHeap *H, size_t y, size_t x) {
  FibNode *t = H->x;
  unlink_(t, y);
  t[y].parent = x;
  t[y].mark = false;
  if (t[x].child == NIL) {
    t[x].child = y;
    t[y].left = t[y].right = y;
  } else {
    size_t c = t[x].child;
    t[y].right = t[c].right;
    t[y].left = c;
    t[t[c].right].left = y;
    t[c].right = y;
  }
  t[x].degree++;
}

static void consolidate(FibHeap *H) {
  size_t A[64], *roots = malloc(H->n * sizeof *roots), r = 0;
  for (size_t i = 0; i < 64; i++) A[i] = NIL;
  size_t w = H->min;
  do { roots[r++] = w; w = H->x[w].right; } while (w != H->min);
  for (size_t i = 0; i < r; i++) {
    size_t x = roots[i], d = H->x[x].degree;
    while (A[d] != NIL) {
      size_t y = A[d];
      if (H->key[y] < H->key[x]) { size_t t = x; x = y; y = t; }
      if (y == H->min) H->min = x;
      link_(H, y, x);
      A[d++] = NIL;
    }
    A[d] = x;
  }
  free(roots);
  H->min = NIL;
  for (size_t d = 0; d < 64; d++)
    if (A[d] != NIL) {
      H->x[A[d]].left = H->x[A[d]].right = A[d];
      spliceIntoRoots(H, A[d]);
    }
}

static size_t fibExtractMin(FibHeap *H) {
  size_t z = H->min;
  FibNode *x = H->x;
  if (x[z].child != NIL) {
    size_t c = x[z].child, *kids = malloc(x[z].degree * sizeof *kids), k = 0;
    do { kids[k++] = c; c = x[c].right; } while (c != x[z].child);
    for (size_t i = 0; i < k; i++) spliceIntoRoots(H, kids[i]);
    free(kids);
  }
  unlink_(x, z);
  x[z].inHeap = false;
  H->min = x[z].right == z ? NIL : x[z].right;
  if (--H->n > 0) consolidate(H);
  return z;
}

static void cut(FibHeap *H, size_t v, size_t p) {
  FibNode *x = H->x;
  if (x[p].child == v) x[p].child = x[v].right == v ? NIL : x[v].right;
  unlink_(x, v);
  x[p].degree--;
  x[v].mark = false;
  spliceIntoRoots(H, v);
}

static void fibDecreaseKey(FibHeap *H, size_t v, double k) {
  H->key[v] = k;
  size_t p = H->x[v].parent;
  if (p != NIL && H->key[v] < H->key[p]) {
    cut(H, v, p);
    for (size_t y = p, z; (z = H->x[y].parent) != NIL; y = z) {
      if (!H->x[y].mark) { H->x[y].mark = true; break; }
      cut(H, y, z);
    }
  }
  if (H->key[v] < H->key[H->min]) H->min = v;
}

void dijkstra(size_t n, const Edge *e, size_t m, size_t src, double *dist, size_t *parent) {
  size_t *start, *adj = adjacency(n, e, m, 0, &start);
  FibHeap H = {malloc(n * sizeof(FibNode)), dist, NIL, 0};
  for (size_t v = 0; v < n; v++) {
    dist[v] = v == src ? 0 : DBL_MAX;
    parent[v] = NIL;
    fibInsert(&H, v);
  }
  while (H.n > 0) {
    size_t u = fibExtractMin(&H);
    if (dist[u] == DBL_MAX) break;
    for (size_t k = start[u]; k < start[u + 1]; k++) {
      const Edge *x = &e[adj[k]];
      if (H.x[x->v].inHeap && dist[u] + x->w < dist[x->v]) {
        parent[x->v] = u;
        fibDecreaseKey(&H, x->v, dist[u] + x->w);
      }
    }
  }
  free(start); free(adj); free(H.x);
}
