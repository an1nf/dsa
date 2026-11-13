#include <stdint.h>
#include <string.h>

#define D 256
#define Q 1000000007ULL

size_t rabinKarpMatcher(const char *T, size_t n, const char *P, size_t m, size_t *shifts) {
  if (m == 0 || m > n) return 0;
  uint64_t h = 1, p = 0, t = 0;
  for (size_t i = 1; i < m; i++) h = h * D % Q;
  for (size_t i = 0; i < m; i++) {
    p = (p * D + (unsigned char)P[i]) % Q;
    t = (t * D + (unsigned char)T[i]) % Q;
  }
  size_t count = 0;
  for (size_t s = 0; s + m <= n; s++) {
    if (p == t && memcmp(T + s, P, m) == 0) shifts[count++] = s;
    if (s + m < n)
      t = ((t + Q - (unsigned char)T[s] * h % Q) * D + (unsigned char)T[s + m]) % Q;
  }
  return count;
}
