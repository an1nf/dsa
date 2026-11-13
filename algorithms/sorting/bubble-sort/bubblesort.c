#include <stdbool.h>
#include <stddef.h>

void bubbleSort(int *a, size_t n) {
  bool swapped = true;
  for (size_t i = 0; i < n && swapped; i++) {
    swapped = false;
    for (size_t j = n - 1; j > i; j--)
      if (a[j] < a[j - 1]) {
        int t = a[j]; a[j] = a[j - 1]; a[j - 1] = t;
        swapped = true;
      }
  }
}
