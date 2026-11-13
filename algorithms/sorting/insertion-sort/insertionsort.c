#include <stddef.h>

void insertionSort(int *a, size_t n) {
  for (size_t i = 1; i < n; i++) {
    int key = a[i];
    size_t j = i;
    for (; j > 0 && a[j - 1] > key; j--)
      a[j] = a[j - 1];
    a[j] = key;
  }
}
