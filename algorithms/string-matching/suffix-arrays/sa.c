#include <stdlib.h>
#include <string.h>

static void sortByRank(size_t *sa, size_t *tmp, const size_t *rank, size_t n,
                       size_t k, size_t maxRank) {
  size_t *c = calloc(maxRank + 2, sizeof *c);
  for (size_t i = 0; i < n; i++) c[sa[i] + k < n ? rank[sa[i] + k] + 1 : 0]++;
  for (size_t r = 1; r < maxRank + 2; r++) c[r] += c[r - 1];
  for (size_t i = n; i--; ) tmp[--c[sa[i] + k < n ? rank[sa[i] + k] + 1 : 0]] = sa[i];
  memcpy(sa, tmp, n * sizeof *sa);
  free(c);
}

size_t *suffixArray(const char *T, size_t n) {
  size_t *sa = malloc(n * sizeof *sa), *rank = malloc(n * sizeof *rank),
         *tmp = malloc(n * sizeof *tmp), maxRank = 255;
  if (n == 0) { free(rank); free(tmp); return sa; }
  for (size_t i = 0; i < n; i++) {
    sa[i] = i;
    rank[i] = (unsigned char)T[i];
  }
  for (size_t k = 1; ; k *= 2) {
    sortByRank(sa, tmp, rank, n, k, maxRank);
    sortByRank(sa, tmp, rank, n, 0, maxRank);
    tmp[sa[0]] = 0;
    for (size_t i = 1; i < n; i++) {
      size_t a = sa[i - 1], b = sa[i];
      int differ = rank[a] != rank[b] ||
                   (a + k < n ? (long)rank[a + k] : -1) != (b + k < n ? (long)rank[b + k] : -1);
      tmp[b] = tmp[a] + differ;
    }
    memcpy(rank, tmp, n * sizeof *rank);
    maxRank = rank[sa[n - 1]];
    if (maxRank + 1 == n || k >= n) break;
  }
  free(rank);
  free(tmp);
  return sa;
}

size_t *lcpArray(const char *T, size_t n, const size_t *sa) {
  size_t *rank = malloc(n * sizeof *rank), *lcp = calloc(n, sizeof *lcp);
  for (size_t i = 0; i < n; i++) rank[sa[i]] = i;
  for (size_t i = 0, h = 0; i < n; i++) {
    if (rank[i] == 0) { h = 0; continue; }
    size_t j = sa[rank[i] - 1];
    while (i + h < n && j + h < n && T[i + h] == T[j + h]) h++;
    lcp[rank[i]] = h;
    if (h > 0) h--;
  }
  free(rank);
  return lcp;
}

static int cmpSuffix(const char *T, size_t n, size_t s, const char *P, size_t m) {
  size_t len = n - s < m ? n - s : m;
  int c = memcmp(T + s, P, len);
  return c ? c : (len < m ? -1 : 0);
}

size_t suffixArrayMatch(const char *T, size_t n, const size_t *sa,
                        const char *P, size_t m, size_t *first) {
  size_t lo = 0, hi = n;
  while (lo < hi) {
    size_t mid = lo + (hi - lo) / 2;
    if (cmpSuffix(T, n, sa[mid], P, m) < 0) lo = mid + 1;
    else hi = mid;
  }
  *first = lo;
  hi = n;
  while (lo < hi) {
    size_t mid = lo + (hi - lo) / 2;
    if (cmpSuffix(T, n, sa[mid], P, m) <= 0) lo = mid + 1;
    else hi = mid;
  }
  return lo - *first;
}
