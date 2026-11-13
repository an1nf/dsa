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

static size_t reachableEdges(size_t n, const Edge *e, size_t m, bool directed,
                             const size_t *start, const size_t *adj, const bool *used,
                             size_t from, bool *seen, size_t *stack) {
  memset(seen, 0, n * sizeof *seen);
  size_t top = 0, count = 0;
  seen[from] = true;
  stack[top++] = from;
  while (top > 0) {
    size_t v = stack[--top];
    for (size_t k = start[v]; k < start[v + 1]; k++) {
      size_t i = adj[k], w = other(e, i, v);
      if (!used[i] && !seen[w]) { seen[w] = true; stack[top++] = w; }
    }
  }
  for (size_t i = 0; i < m; i++)
    count += !used[i] && (seen[e[i].u] || (!directed && seen[e[i].v]));
  return count;
}

bool fleury(size_t n, const Edge *e, size_t m, bool directed, size_t *path) {
  size_t v = startVertex(n, e, m, directed);
  if (v == SIZE_MAX) return false;
  size_t *start, *adj = adjacency(n, e, m, directed, &start), *stack = malloc(n * sizeof *stack);
  bool *used = calloc(m, sizeof *used), *seen = malloc(n * sizeof *seen), ok = true;
  path[0] = v;
  for (size_t step = 0; step < m && ok; step++) {
    size_t chosen = SIZE_MAX, fallback = SIZE_MAX, remaining = m - step - 1;
    for (size_t k = start[v]; k < start[v + 1]; k++) {
      size_t i = adj[k];
      if (used[i]) continue;
      if (fallback == SIZE_MAX) fallback = i;
      used[i] = true;
      size_t r = reachableEdges(n, e, m, directed, start, adj, used, other(e, i, v), seen, stack);
      used[i] = false;
      if (r == remaining) { chosen = i; break; }
    }
    if (chosen == SIZE_MAX) chosen = fallback;
    if (chosen == SIZE_MAX) ok = false;
    else {
      used[chosen] = true;
      v = other(e, chosen, v);
      path[step + 1] = v;
    }
  }
  free(start); free(adj); free(stack); free(used); free(seen);
  return ok;
}
