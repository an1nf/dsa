#include <float.h>
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

typedef struct { size_t n, *heap, *pos; double *key; } MinPQ;

static void swapAt(MinPQ *q, size_t i, size_t j) {
  size_t t = q->heap[i]; q->heap[i] = q->heap[j]; q->heap[j] = t;
  q->pos[q->heap[i]] = i;
  q->pos[q->heap[j]] = j;
}

static void siftUp(MinPQ *q, size_t i) {
  for (; i > 0 && q->key[q->heap[(i - 1) / 2]] > q->key[q->heap[i]]; i = (i - 1) / 2)
    swapAt(q, i, (i - 1) / 2);
}

static size_t extractMin(MinPQ *q) {
  size_t min = q->heap[0];
  swapAt(q, 0, --q->n);
  q->pos[min] = SIZE_MAX;
  for (size_t i = 0;;) {
    size_t l = 2 * i + 1, r = l + 1, s = i;
    if (l < q->n && q->key[q->heap[l]] < q->key[q->heap[s]]) s = l;
    if (r < q->n && q->key[q->heap[r]] < q->key[q->heap[s]]) s = r;
    if (s == i) break;
    swapAt(q, i, s);
    i = s;
  }
  return min;
}

static void decreaseKey(MinPQ *q, size_t v, double k) {
  q->key[v] = k;
  siftUp(q, q->pos[v]);
}

void dijkstra(size_t n, const Edge *e, size_t m, size_t src, double *dist, size_t *parent) {
  size_t *start, *adj = adjacency(n, e, m, 0, &start);
  MinPQ q = {n, malloc(n * sizeof(size_t)), malloc(n * sizeof(size_t)), dist};
  for (size_t v = 0; v < n; v++) {
    q.heap[v] = q.pos[v] = v;
    dist[v] = DBL_MAX;
    parent[v] = SIZE_MAX;
  }
  decreaseKey(&q, src, 0);
  while (q.n > 0) {
    size_t u = extractMin(&q);
    if (dist[u] == DBL_MAX) break;
    for (size_t k = start[u]; k < start[u + 1]; k++) {
      const Edge *x = &e[adj[k]];
      if (q.pos[x->v] != SIZE_MAX && dist[u] + x->w < dist[x->v]) {
        parent[x->v] = u;
        decreaseKey(&q, x->v, dist[u] + x->w);
      }
    }
  }
  free(start); free(adj); free(q.heap); free(q.pos);
}
