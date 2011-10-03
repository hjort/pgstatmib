#include <stdio.h>		/* gets */
#include <stdlib.h>		/* atoi, malloc */
#include <string.h>		/* strcpy */
#include <uthash.h>

#define CACHE_TIMEOUT	10	// in seconds

// based on /proc/net/dev
typedef struct iface
{
  int id;			/* key */

  char name[10];
  long rxbytes;
  int rxpacks;
  long txbytes;
  int txpacks;

  time_t last;

  UT_hash_handle hh;		/* makes this structure hashable */
} ifStats;

ifStats *stats = NULL;
//static int iface_count = 0;

/*
void
delete_user (User * user)
{
  HASH_DEL (users, user);	// user: pointer to deletee
  free (user);
}

void
delete_all ()
{
  User *current_user;

  while (users)
    {
      current_user = users;	// grab pointer to first item
      HASH_DEL (users, current_user);	// delete it (users advances to next)
      free (current_user);	// free it
    }
}
*/

const char *IFACE_NAMES[] = { "lo", "eth0", "wlan0" };

int
load_iface_stats (int id, ifStats * s)
{
  strcpy (s->name, id >=1 && id <= 3 ? IFACE_NAMES[id - 1] : "unknown");
  s->rxbytes += id * 100;
  s->rxpacks += id * 1;
  s->txbytes += id * 50;
  s->txpacks += id * 5;
  return 0;
}

/*
int
load_all_iface_stats (void)
{
  int i;
  ifStats *s;
  time_t now;

  now = time (NULL);

  for (i = 1; i <= 3; i++)
    {
      s = (ifStats *) malloc (sizeof (ifStats));
      HASH_ADD_INT (stats, id, s);
      load_iface_stats (i, s);
      s->last = now;
    }
  iface_count = 3;

  return 0;
}
*/

ifStats *
get_iface_stats (int id)
{
  ifStats *s;
  time_t now;
  unsigned int diff;

  diff = CACHE_TIMEOUT;
  now = time (NULL);

	fprintf(stderr, "id: %d, &id: %d\n", id, (int) &id);
  HASH_FIND_INT (stats, &id, s);
	fprintf(stderr, "s: %s\n", (char *) s);

  if (!s)
    {
		fprintf(stderr, "id %d not in cache...\n", id);
      s = (ifStats *) malloc (sizeof (ifStats));
      s->id = id;
      HASH_ADD_INT (stats, id, s);
    }
  else
    {
		diff = (now - s->last);
		fprintf(stderr, "cache diff: %ds\n", diff);
    }

  if (diff >= CACHE_TIMEOUT)
    {
		fprintf(stderr, "reloading of id %d is needed...\n", id);
      load_iface_stats (id, s);
    }

  s->last = now;

  return s;
}

void
show_iface_stats (ifStats * s)
{
  printf ("interface: %s\n", s->name);
  printf ("received: %d bytes (%d packages)\n", (int) s->rxbytes, s->rxpacks);
  printf ("transmitted: %d bytes (%d packages)\n", (int) s->txbytes, s->txpacks);
}

void
show_all_iface_stats ()
{
  ifStats *s;
  for (s = stats; s != NULL; s = (ifStats *) (s->hh.next))
    {
      show_iface_stats (s);
      printf ("\n");
    }
}

int
main (int argc, char *argv[])
{
  char in[10];
  ifStats *s;
  int id;

  while (1)
    {
      printf ("1. get iface stats\n");
      printf ("2. show all iface stats\n");
      gets (in);
      switch (atoi (in))
	{
	case 1:
	  printf ("iface number: ");
          id = atoi (gets (in));
	  s = get_iface_stats (id);
	  show_iface_stats (s);
	  printf ("\n");
	  break;
	case 2:
	  show_all_iface_stats ();
	  break;
	default:
	  return 0;
	}
    }
}

int main3(void)
{
  int id, cont;
  ifStats *s;
  for (cont = 1; cont <= 2; cont++)
    for (id = 1; id <= 3; id++) {
      s = get_iface_stats (id);
      sleep(1);
    }
  show_all_iface_stats ();
}

int main4(void)
{
  int id, cont;
  ifStats *s;
  for (cont = 1; cont <= 2; cont++)
    for (id = 1; id <= 3; id++) {
      HASH_FIND_INT (stats, &id, s);

      if (!s)
      {
	fprintf(stderr, "id %d not in cache...\n", id);
        s = (ifStats *) malloc (sizeof (ifStats));
        s->id = id;
        HASH_ADD_INT (stats, id, s);
        load_iface_stats (id, s);
      }

      sleep(1);
    }
  show_all_iface_stats ();
}

