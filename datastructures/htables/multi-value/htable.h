#ifndef HTABLE_H
#define HTABLE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct HtEntry {
  char *key;
  int *values;
  size_t nValues, capacity;
  struct HtEntry *next;
} HtEntry;

typedef struct {
  HtEntry **buckets;
  size_t capacity, size;
} HashTable;

HashTable *htNew(size_t capacity);
void htFree(HashTable *H);
void htAdd(HashTable *H, const char *key, int value);
const int *htGet(const HashTable *H, const char *key, size_t *nValues);
bool htDeleteValue(HashTable *H, const char *key, int value);
bool htDeleteKey(HashTable *H, const char *key);

#endif
