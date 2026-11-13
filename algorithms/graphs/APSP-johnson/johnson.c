#include <math.h>
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

static void dijkstra(size_t n, const Edge *e, const double *w, const size_t *start,
                     const size_t *adj, size_t src, double *dist) {
  MinPQ q = {n, malloc(n * sizeof(size_t)), malloc(n * sizeof(size_t)), dist};
  for (size_t v = 0; v < n; v++) {
    q.heap[v] = q.pos[v] = v;
    dist[v] = INFINITY;
  }
  decreaseKey(&q, src, 0);
  while (q.n > 0) {
    size_t u = extractMin(&q);
    if (isinf(dist[u])) break;
    for (size_t k = start[u]; k < start[u + 1]; k++) {
      size_t i = adj[k], v = e[i].v;
      if (q.pos[v] != SIZE_MAX && dist[u] + w[i] < dist[v]) decreaseKey(&q, v, dist[u] + w[i]);
    }
  }
  free(q.heap);
  free(q.pos);
}

bool johnson(size_t n, const Edge *e, size_t m, double *D) {
  double *h = calloc(n, sizeof *h), *w = malloc(m * sizeof *w);
  for (size_t r = 0; r < n; r++)
    for (size_t i = 0; i < m; i++)
      if (h[e[i].u] + e[i].w < h[e[i].v]) h[e[i].v] = h[e[i].u] + e[i].w;
  for (size_t i = 0; i < m; i++)
    if (h[e[i].u] + e[i].w < h[e[i].v]) {
      free(h);
      free(w);
      return false;
    }
  for (size_t i = 0; i < m; i++) w[i] = e[i].w + h[e[i].u] - h[e[i].v];

  size_t *start, *adj = adjacency(n, e, m, 0, &start);
  for (size_t u = 0; u < n; u++) {
    dijkstra(n, e, w, start, adj, u, D + u * n);
    for (size_t v = 0; v < n; v++) D[u * n + v] += h[v] - h[u];
  }
  free(h); free(w); free(start); free(adj);
  return true;
}
