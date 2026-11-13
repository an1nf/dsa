#include <stdint.h>
#include <stdlib.h>

typedef struct { size_t start, finish; } Activity;

static size_t collect(const size_t *split, size_t N, size_t i, size_t j, size_t *out) {
  size_t k = split[i * N + j];
  if (k == 0) return 0;
  size_t c = collect(split, N, i, k, out);
  out[c++] = k - 1;
  return c + collect(split, N, k, j, out + c);
}

size_t dpActivitySelector(const Activity *a, size_t n, size_t *out) {
  size_t N = n + 2;
  Activity *s = malloc(N * sizeof *s);
  s[0] = (Activity){0, 0};
  for (size_t i = 0; i < n; i++) s[i + 1] = a[i];
  s[n + 1] = (Activity){SIZE_MAX, SIZE_MAX};
  size_t *c = calloc(N * N, sizeof *c), *split = calloc(N * N, sizeof *split);

  for (size_t l = 2; l < N; l++)
    for (size_t i = 0; i + l < N; i++) {
      size_t j = i + l;
      for (size_t k = i + 1; k < j; k++)
        if (s[i].finish <= s[k].start && s[k].finish <= s[j].start &&
            c[i * N + k] + c[k * N + j] + 1 > c[i * N + j]) {
          c[i * N + j] = c[i * N + k] + c[k * N + j] + 1;
          split[i * N + j] = k;
        }
    }
  size_t count = collect(split, N, 0, n + 1, out);
  free(s); free(c); free(split);
  return count;
}
