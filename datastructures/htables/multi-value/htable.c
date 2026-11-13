#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "htable.h"

static uint64_t hash(const char *s) {
  uint64_t h = 1469598103934665603ULL;
  while (*s) h = (h ^ (unsigned char)*s++) * 1099511628211ULL;
  return h;
}

HashTable *htNew(size_t capacity) {
  HashTable *H = malloc(sizeof *H);
  H->capacity = capacity ? capacity : 1;
  H->buckets = calloc(H->capacity, sizeof *H->buckets);
  H->size = 0;
  return H;
}

static void freeEntry(HtEntry *e) {
  free(e->key);
  free(e->values);
  free(e);
}

void htFree(HashTable *H) {
  for (size_t i = 0; i < H->capacity; i++)
    for (HtEntry *e = H->buckets[i], *next; e; e = next) {
      next = e->next;
      freeEntry(e);
    }
  free(H->buckets);
  free(H);
}

static HtEntry **find(const HashTable *H, const char *key) {
  HtEntry **e = &H->buckets[hash(key) % H->capacity];
  while (*e && strcmp((*e)->key, key) != 0) e = &(*e)->next;
  return e;
}

static void rehash(HashTable *H) {
  size_t old = H->capacity;
  HtEntry **buckets = H->buckets;
  H->capacity *= 2;
  H->buckets = calloc(H->capacity, sizeof *H->buckets);
  for (size_t i = 0; i < old; i++)
    for (HtEntry *e = buckets[i], *next; e; e = next) {
      next = e->next;
      HtEntry **b = &H->buckets[hash(e->key) % H->capacity];
      e->next = *b;
      *b = e;
    }
  free(buckets);
}

void htAdd(HashTable *H, const char *key, int value) {
  HtEntry **e = find(H, key);
  if (!*e) {
    HtEntry *x = calloc(1, sizeof *x);
    x->key = malloc(strlen(key) + 1);
    strcpy(x->key, key);
    *e = x;
    if (++H->size > H->capacity) {
      rehash(H);
      e = find(H, key);
    }
  }
  HtEntry *x = *e;
  if (x->nValues == x->capacity) {
    x->capacity = x->capacity ? 2 * x->capacity : 4;
    x->values = realloc(x->values, x->capacity * sizeof *x->values);
  }
  x->values[x->nValues++] = value;
}

const int *htGet(const HashTable *H, const char *key, size_t *nValues) {
  HtEntry *e = *find(H, key);
  *nValues = e ? e->nValues : 0;
  return e ? e->values : NULL;
}

bool htDeleteValue(HashTable *H, const char *key, int value) {
  HtEntry *e = *find(H, key);
  if (!e) return false;
  for (size_t i = 0; i < e->nValues; i++)
    if (e->values[i] == value) {
      e->values[i] = e->values[--e->nValues];
      return true;
    }
  return false;
}

bool htDeleteKey(HashTable *H, const char *key) {
  HtEntry **e = find(H, key), *x = *e;
  if (!x) return false;
  *e = x->next;
  freeEntry(x);
  H->size--;
  return true;
}
