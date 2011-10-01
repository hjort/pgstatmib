#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CACHE_BUF 100
#define MAX_CACHE_ENTRIES 10

typedef struct
{
  void *block;
  size_t numBytes;
} cacheEntry_t;

typedef struct
{
  cacheEntry_t *cache;
  size_t numCacheEntries;
} Cache_t;

void addToCache (Cache_t *, void *, size_t);
void showCache (Cache_t *);
void deleteCache (Cache_t *);
int rnd (int range);

int
main (int argc, char *argv[])
{
  time_t t;
  char *buf;
  size_t i, n;
  Cache_t C;

  C.cache = calloc (MAX_CACHE_ENTRIES, sizeof (cacheEntry_t));
  C.numCacheEntries = 0;
  srand ((unsigned) time (&t));
  for (i = 0; i < 5; i++)
    {
      buf = (char *) malloc (n = rnd (MAX_CACHE_BUF));
      addToCache (&C, buf, n);
    }
  showCache (&C);
  deleteCache (&C);

  return 0;
}

void
addToCache (Cache_t * C, void *mem, size_t bytes)
{
  C->cache[C->numCacheEntries].block = malloc (bytes);
  memcpy (C->cache[C->numCacheEntries].block, mem, bytes);
  C->cache[C->numCacheEntries].numBytes = bytes;
  ++C->numCacheEntries;
}

void
showCache (Cache_t * C)
{
  size_t i;

  for (i = 0; i < C->numCacheEntries; i++)
    {
      printf ("\n%2d. %2d bytes at 0x%X",
	      i, C->cache[i].numBytes, (int) C->cache[i].block);
    }
printf("\n");
}

void
deleteCache (Cache_t * C)
{
  size_t i;

  for (i = 0; i < C->numCacheEntries; i++)
    {
      free (C->cache[i].block);
    }
  free (C->cache);
}

int
rnd (int range)
{
  float x = ((float) rand () / (float) RAND_MAX) * range;
  return (int) x;
}
