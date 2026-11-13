#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"

static uint64_t hash(const char *s) {
  uint64_t h = 1469598103934665603ULL;
  while (*s) h = (h ^ (unsigned char)*s++) * 1099511628211ULL;
  return h;
}

Map *mapNew(size_t capacity) {
  Map *M = malloc(sizeof *M);
  M->capacity = capacity ? capacity : 1;
  M->buckets = calloc(M->capacity, sizeof *M->buckets);
  M->size = 0;
  return M;
}

void mapFree(Map *M) {
  for (size_t i = 0; i < M->capacity; i++)
    for (Entry *e = M->buckets[i], *next; e; e = next) {
      next = e->next;
      free(e->key);
      free(e);
    }
  free(M->buckets);
  free(M);
}

static Entry **find(const Map *M, const char *key) {
  Entry **e = &M->buckets[hash(key) % M->capacity];
  while (*e && strcmp((*e)->key, key) != 0) e = &(*e)->next;
  return e;
}

static void rehash(Map *M) {
  size_t old = M->capacity;
  Entry **buckets = M->buckets;
  M->capacity *= 2;
  M->buckets = calloc(M->capacity, sizeof *M->buckets);
  for (size_t i = 0; i < old; i++)
    for (Entry *e = buckets[i], *next; e; e = next) {
      next = e->next;
      Entry **b = &M->buckets[hash(e->key) % M->capacity];
      e->next = *b;
      *b = e;
    }
  free(buckets);
}

void mapPut(Map *M, const char *key, int value) {
  Entry **e = find(M, key);
  if (*e) {
    (*e)->value = value;
    return;
  }
  Entry *x = malloc(sizeof *x);
  x->key = malloc(strlen(key) + 1);
  strcpy(x->key, key);
  x->value = value;
  x->next = NULL;
  *e = x;
  if (++M->size > M->capacity) rehash(M);
}

bool mapGet(const Map *M, const char *key, int *value) {
  Entry *e = *find(M, key);
  if (e) *value = e->value;
  return e != NULL;
}

bool mapDelete(Map *M, const char *key) {
  Entry **e = find(M, key), *x = *e;
  if (!x) return false;
  *e = x->next;
  free(x->key);
  free(x);
  M->size--;
  return true;
}
