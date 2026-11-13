#include <stdint.h>
#include <stdlib.h>

#define MOD 998244353ULL
#define ROOT 3ULL

static uint64_t power(uint64_t b, uint64_t e) {
  uint64_t r = 1;
  for (b %= MOD; e; e >>= 1, b = b * b % MOD)
    if (e & 1) r = r * b % MOD;
  return r;
}

void ntt(uint64_t *a, size_t n, int inverse) {
  for (size_t i = 1, j = 0; i < n; i++) {
    size_t bit = n >> 1;
    for (; j & bit; bit >>= 1) j ^= bit;
    j |= bit;
    if (i < j) { uint64_t t = a[i]; a[i] = a[j]; a[j] = t; }
  }
  for (size_t m = 2; m <= n; m <<= 1) {
    uint64_t wm = power(ROOT, (MOD - 1) / m);
    if (inverse) wm = power(wm, MOD - 2);
    for (size_t k = 0; k < n; k += m) {
      uint64_t w = 1;
      for (size_t j = 0; j < m / 2; j++) {
        uint64_t t = w * a[k + j + m / 2] % MOD, u = a[k + j];
        a[k + j] = (u + t) % MOD;
        a[k + j + m / 2] = (u + MOD - t) % MOD;
        w = w * wm % MOD;
      }
    }
  }
  if (inverse) {
    uint64_t nInv = power(n, MOD - 2);
    for (size_t i = 0; i < n; i++) a[i] = a[i] * nInv % MOD;
  }
}

uint64_t *polyMultiplyMod(const uint64_t *x, size_t nx, const uint64_t *y, size_t ny) {
  size_t n = 1;
  while (n < nx + ny) n <<= 1;
  uint64_t *a = calloc(n, sizeof *a), *b = calloc(n, sizeof *b);
  for (size_t i = 0; i < nx; i++) a[i] = x[i] % MOD;
  for (size_t i = 0; i < ny; i++) b[i] = y[i] % MOD;
  ntt(a, n, 0);
  ntt(b, n, 0);
  for (size_t i = 0; i < n; i++) a[i] = a[i] * b[i] % MOD;
  ntt(a, n, 1);
  free(b);
  return a;
}
