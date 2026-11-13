#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef enum { COPY, INSERT, DELETE, REPLACE, TWIDDLE, KILL } Op;

typedef struct {
  const char *x, *y;
  size_t n;
  const size_t *cost;
  size_t *memo;
  Op *op;
} Ctx;

static size_t dist(Ctx *c, size_t i, size_t j) {
  size_t k = i * (c->n + 1) + j;
  if (c->memo[k] != SIZE_MAX) return c->memo[k];
  if (i == 0) return c->memo[k] = j * c->cost[INSERT];
  if (j == 0) return c->memo[k] = i * c->cost[DELETE];
  const char *x = c->x, *y = c->y;
  Op o = x[i - 1] == y[j - 1] ? COPY : REPLACE, bestOp = o;
  size_t d, best = dist(c, i - 1, j - 1) + c->cost[o];
  if (i > 1 && j > 1 && x[i - 1] == y[j - 2] && x[i - 2] == y[j - 1] &&
      (d = dist(c, i - 2, j - 2) + c->cost[TWIDDLE]) < best) { best = d; bestOp = TWIDDLE; }
  if ((d = dist(c, i, j - 1) + c->cost[INSERT]) < best) { best = d; bestOp = INSERT; }
  if ((d = dist(c, i - 1, j) + c->cost[DELETE]) < best) { best = d; bestOp = DELETE; }
  c->op[k] = bestOp;
  return c->memo[k] = best;
}

size_t memoizedEditSequence(const char *x, const char *y, const size_t *cost,
                            Op *seq, size_t *len) {
  size_t m = strlen(x), n = strlen(y), cells = (m + 1) * (n + 1);
  Ctx c = {x, y, n, cost, malloc(cells * sizeof(size_t)), malloc(cells * sizeof(Op))};
  for (size_t i = 0; i < cells; i++) c.memo[i] = SIZE_MAX;
  size_t best = dist(&c, m, n), killFrom = m;
  for (size_t k = 0; k < m; k++) {
    size_t d = dist(&c, k, n) + cost[KILL];
    if (d < best) { best = d; killFrom = k; }
  }

  size_t s = 0, i = killFrom, j = n;
  if (killFrom < m) seq[s++] = KILL;
  while (i > 0 || j > 0) {
    Op o = i == 0 ? INSERT : j == 0 ? DELETE : c.op[i * (n + 1) + j];
    seq[s++] = o;
    if (o == INSERT) j--;
    else if (o == DELETE) i--;
    else if (o == TWIDDLE) { i -= 2; j -= 2; }
    else { i--; j--; }
  }
  for (size_t a = 0, b = s; a + 1 < b--; a++) { Op t = seq[a]; seq[a] = seq[b]; seq[b] = t; }
  *len = s;
  free(c.memo);
  free(c.op);
  return best;
}
