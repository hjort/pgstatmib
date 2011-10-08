#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpq-fe.h>
#include <uthash.h>

typedef struct db_struct
{
  int id;			/* key */
  char name[10];

  PGconn *conn;

  UT_hash_handle hh;		/* makes this structure hashable */
} DBconn;

DBconn *databases = NULL;

int
add_database (int datid, char *datname)
{
  DBconn *db;
  db = (DBconn *) malloc (sizeof (DBconn));
  db->id = datid;
  strcpy (db->name, datname);
  HASH_ADD_INT (databases, id, db);	/* id: name of key field */
}

int
name_sort (DBconn * a, DBconn * b)
{
  return strcmp (a->name, b->name);
}

void
sort_by_name ()
{
  HASH_SORT (databases, name_sort);
}

DBconn *
find_database (int datid)
{
  DBconn *db;
  HASH_FIND_INT (databases, &datid, db);	/* db: output pointer */
//  fprintf (stdout, "find_database(%d) = %d\n", datid, (int) db);
  return db;
}

int
start_connection (DBconn * db)
{
  char conninfo[255];
  PGconn *conn;

//  fprintf (stdout, "start_connection(%d)\n", (int) db);

//printf("db = %d, db->conn = %d, db->name = %s\n", (int) db, (int) db->conn, db->name);

  if (!db->conn)
    {
      sprintf (conninfo, "dbname=%s user=%s", db->name, "postgres");
//printf("conninfo = %s\n", conninfo);
      conn = PQconnectdb (conninfo);
//printf("conn = %d\n", (int) conn);
      if (PQstatus (conn) != CONNECTION_OK)
	{
	  fprintf (stderr, "Connection to database %s failed: %s",
		   db->name, PQerrorMessage (conn));
	}
      else
	{
	  db->conn = conn;
	}
    }
  return 0;
}

int
release_connection (DBconn * db)
{
  fprintf (stdout, "release_connection(%d)\n", (int) db);
  if (db->conn)
    {
      PQfinish (db->conn);
    }
  return 0;
}

int
remove_database (DBconn * db)
{
  release_connection (db);
  HASH_DEL (databases, db);
  free (db);
  return 0;
}

#define	USER_TABLES	1
#define	SYSTEM_TABLES	2
#define ALL_TABLES	3

void
show_table_stats (int datid, int filter)
{
  DBconn *db;
  PGresult *res;
  int nFields, i, j;
  char sql[100];

  //fprintf (stdout, "show_table_stats(%d, %d)\n", datid, filter);

  db = find_database (datid);
  if (db && db->conn)
    {

      strcpy (sql, "SELECT relid, relname, seq_scan, idx_scan FROM pg_stat_");
      if (filter == USER_TABLES)
	strcat (sql, "user");
      else if (filter == SYSTEM_TABLES)
	strcat (sql, "sys");
      else
	strcat (sql, "all");
      strcat (sql, "_tables");
      strcat (sql, " LIMIT 5");

      fprintf (stdout, "conn: %d, sql: %s\n", (int) db->conn, sql);

      res = PQexec (db->conn, sql);
      if (PQresultStatus (res) != PGRES_TUPLES_OK)
	{
	  fprintf (stderr, "SELECT command failed: %s",
		   PQerrorMessage (db->conn));
	  PQclear (res);
	  //exit_nicely(conn);
	}

      nFields = PQnfields (res);
      for (i = 0; i < nFields; i++)
	printf ("%-20s", PQfname (res, i));
      printf ("\n");

      for (i = 0; i < PQntuples (res); i++)
	{
	  for (j = 0; j < nFields; j++)
	    printf ("%-20s", PQgetvalue (res, i, j));
	  printf ("\n");
	}
      PQclear (res);

    }
}

static void
exit_nicely (PGconn * conn)
{
  PQfinish (conn);
  exit (1);
}

int
main (int argc, char **argv)
{
  const char *conninfo;
  PGconn *conn;
  PGresult *res;
  int nFields, i, j;
  char *datname;
  int datid;
  DBconn *db;

  /*
   * If the user supplies a parameter on the command line, use it as the
   * conninfo string; otherwise default to setting dbname=postgres and using
   * environment variables or defaults for all other connection parameters.
   */
  if (argc > 1)
    conninfo = argv[1];
  else
    conninfo = "dbname = postgres";

  /* Make a connection to the database */
  conn = PQconnectdb (conninfo);

  /* Check to see that the backend connection was successfully made */
  if (PQstatus (conn) != CONNECTION_OK)
    {
      fprintf (stderr, "Connection to database failed: %s",
	       PQerrorMessage (conn));
      exit_nicely (conn);
    }

  res =
    PQexec (conn,
	    "SELECT oid, datname FROM pg_database WHERE datname !~ '^template' ORDER BY oid");
  if (PQresultStatus (res) != PGRES_TUPLES_OK)
    {
      fprintf (stderr, "SELECT command failed: %s", PQerrorMessage (conn));
      PQclear (res);
      exit_nicely (conn);
    }

  nFields = PQnfields (res);
  /*for (i = 0; i < nFields; i++)
     printf("%-15s", PQfname(res, i));
     printf("\n\n"); */

  for (i = 0; i < PQntuples (res); i++)
    {
      /*for (j = 0; j < nFields; j++)
         printf ("%-15s", PQgetvalue (res, i, j));
         printf ("\n"); */

      datid = atoi (PQgetvalue (res, i, 0));
      datname = PQgetvalue (res, i, 1);
      add_database (datid, datname);
    }
  PQclear (res);

  /* close the connection to the database and cleanup */
  PQfinish (conn);

  // loop through all databases
  sort_by_name ();
  for (db = databases; db != NULL; db = (DBconn *) (db->hh.next))
    {

      printf ("\ndatabase id: %d, name: %s\n", db->id, db->name);

      // TODO: call find_database() somewhere

      start_connection (db);

//      printf("user tables:\n");
      show_table_stats (db->id, USER_TABLES);

//      printf("system tables:\n");
      //    show_table_stats (db->id, SYSTEM_TABLES);
    }

  // free resources
  while (databases)
    {
      db = databases;
      remove_database (db);
    }

  return 0;
}
