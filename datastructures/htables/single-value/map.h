#ifndef MAP_H
#define MAP_H

#include <stdbool.h>
#include <stddef.h>

typedef struct Entry {
  char *key;
  int value;
  struct Entry *next;
} Entry;

typedef struct {
  Entry **buckets;
  size_t capacity, size;
} Map;

Map *mapNew(size_t capacity);
void mapFree(Map *M);
void mapPut(Map *M, const char *key, int value);
bool mapGet(const Map *M, const char *key, int *value);
bool mapDelete(Map *M, const char *key);

#endif
