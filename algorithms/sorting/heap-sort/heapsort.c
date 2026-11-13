#include <stddef.h>

static void swap(int *x, int *y) { int t = *x; *x = *y; *y = t; }

static void maxHeapify(int *a, size_t n, size_t i) {
  for (;;) {
    size_t l = 2 * i + 1, r = l + 1, m = i;
    if (l < n && a[l] > a[m]) m = l;
    if (r < n && a[r] > a[m]) m = r;
    if (m == i) return;
    swap(&a[i], &a[m]);
    i = m;
  }
}

void heapSort(int *a, size_t n) {
  for (size_t i = n / 2; i--; )
    maxHeapify(a, n, i);
  for (size_t i = n; i-- > 1; ) {
    swap(&a[0], &a[i]);
    maxHeapify(a, i, 0);
  }
}
