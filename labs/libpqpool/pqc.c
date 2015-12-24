#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libpq-fe.h"

/*
/src/interfaces/libpq/libpq-fe.h:
  typedef struct pg_conn PGconn;

/src/interfaces/libpq/libpq-int.h:
  struct pg_conn
  {
    char *pghost;
    char *pghostaddr;
    char *pgport;
    char *pgunixsocket;
    ...
  };
*/

/*
gcc -I/usr/src/postgresql-9.3/src/interfaces/libpq -I/usr/src/postgresql-9.3/src/include pqc.c -L/usr/src/postgresql-9.3/src/interfaces/libpq -lpq -lpthread -o pqc
*/

//#define MAX_DATABASES 20

int main(int argc, char **argv)
{
	PGconn **conns; // dynamically allocated vector
	//PGconn *conns[MAX_DATABASES]; // fixed-size vector
	int i, ndbs;

	ndbs = 3; // this value may vary

	conns = malloc(ndbs * sizeof(*conns));
	//memset(conns, 0, sizeof(conns));

	// instantiate connections
	for (i = 0; i < ndbs; i++) {
		conns[i] = PQconnectdb("dbname=template1");
		fprintf(stdout, "%d) %p\n", i + 1, conns[i]);
	}

	// release connections
	for (i = 0; i < ndbs; i++) {
		fprintf(stdout, "%d) %p\n", i + 1, conns[i]);
		if (conns[i])
			PQfinish(conns[i]);
	}

	free(conns);

	return 0;
}

