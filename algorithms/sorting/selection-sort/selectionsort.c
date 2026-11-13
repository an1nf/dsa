#include <stddef.h>

void selectionSort(int *a, size_t n) {
  for (size_t i = 0; i + 1 < n; i++) {
    size_t min = i;
    for (size_t j = i + 1; j < n; j++)
      if (a[j] < a[min]) min = j;
    int t = a[i]; a[i] = a[min]; a[min] = t;
  }
}
