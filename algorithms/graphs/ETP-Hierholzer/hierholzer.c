#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct { size_t u, v; } Edge;

static size_t *adjacency(size_t n, const Edge *e, size_t m, bool directed, size_t **start) {
  size_t *s = calloc(n + 1, sizeof *s), *adj = malloc(2 * m * sizeof *adj),
         *pos = malloc(n * sizeof *pos);
  for (size_t i = 0; i < m; i++) {
    s[e[i].u + 1]++;
    if (!directed) s[e[i].v + 1]++;
  }
  for (size_t v = 0; v < n; v++) s[v + 1] += s[v];
  memcpy(pos, s, n * sizeof *pos);
  for (size_t i = 0; i < m; i++) {
    adj[pos[e[i].u]++] = i;
    if (!directed) adj[pos[e[i].v]++] = i;
  }
  free(pos);
  *start = s;
  return adj;
}

static size_t startVertex(size_t n, const Edge *e, size_t m, bool directed) {
  long *bal = calloc(n, sizeof *bal);
  size_t start = m ? e[0].u : 0, plus = 0, minus = 0;
  bool bad = false;
  for (size_t i = 0; i < m; i++) {
    bal[e[i].u]++;
    bal[e[i].v] += directed ? -1 : 1;
  }
  for (size_t v = 0; v < n; v++) {
    long b = directed ? bal[v] : bal[v] % 2;
    if (b == 1) { plus++; start = v; }
    else if (b == -1) minus++;
    else if (b != 0) bad = true;
  }
  free(bal);
  bool ok = directed ? !bad && plus == minus && plus <= 1 : plus == 0 || plus == 2;
  return ok ? start : SIZE_MAX;
}

static size_t other(const Edge *e, size_t i, size_t v) { return e[i].u == v ? e[i].v : e[i].u; }

bool hierholzer(size_t n, const Edge *e, size_t m, bool directed, size_t *path) {
  size_t s = startVertex(n, e, m, directed);
  if (s == SIZE_MAX) return false;
  size_t *start, *adj = adjacency(n, e, m, directed, &start), *it = malloc(n * sizeof *it),
         *stack = malloc((m + 1) * sizeof *stack), top = 0, len = 0;
  bool *used = calloc(m, sizeof *used);
  memcpy(it, start, n * sizeof *it);
  stack[top++] = s;
  while (top > 0) {
    size_t v = stack[top - 1];
    while (it[v] < start[v + 1] && used[adj[it[v]]]) it[v]++;
    if (it[v] == start[v + 1]) path[len++] = stack[--top];
    else {
      size_t i = adj[it[v]];
      used[i] = true;
      stack[top++] = other(e, i, v);
    }
  }
  for (size_t i = 0, j = len - 1; i < j; i++, j--) {
    size_t t = path[i]; path[i] = path[j]; path[j] = t;
  }
  free(start); free(adj); free(it); free(stack); free(used);
  return len == m + 1;
}
