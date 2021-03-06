#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "libpq-fe.h"

#define MAX_DATABASES 20
#define MAX_NAME_LENGTH 50
#define MAX_SQL_THREADS 5

void *run(void *);

char dbnames[MAX_DATABASES][MAX_NAME_LENGTH];
PGconn **conns;
pthread_mutex_t *locks;

int
main(int argc, char **argv)
{
	char conninfo[MAX_NAME_LENGTH + 7];
	PGconn *conn;
	PGresult *res;
	int i, j, ndbs, nreqs, ret;
	pthread_t **threads;
	//pthread_t thread[MAX_DATABASES][MAX_SQL_THREADS];

	memset(dbnames, 0, sizeof(dbnames));

	// 1. connect to 'template1' database
	strcpy(conninfo, "dbname=template1");
	conn = PQconnectdb(conninfo);
	if (PQstatus(conn) != CONNECTION_OK) {
		fprintf(stderr, "ERROR 1: %s", PQerrorMessage(conn));
		PQfinish(conn);
		return 1;
	} else {
		fprintf(stdout, "Connected!\n");
	}

	// 2. retrieve existing database names
	res = PQexec(conn, "SELECT datname FROM pg_database ORDER BY 1");
	if (PQresultStatus(res) != PGRES_TUPLES_OK) {
		fprintf(stderr, "ERROR 2: %s\n", PQerrorMessage(conn));
		PQclear(res);
		PQfinish(conn);
		return 2;
	}
	ndbs = PQntuples(res);
	fprintf(stdout, "Found %d databases:\n", ndbs);
	for (i = 0; i < ndbs; i++) {
		strcpy(dbnames[i], PQgetvalue(res, i, 0));
		printf("  %s\n", dbnames[i]);
	}
	PQclear(res);

	// 3. make a connection to each database
	conns = malloc(ndbs * sizeof(PGconn*));
	fprintf(stdout, "Making connections:\n");
	for (i = 0; i < ndbs; i++) {
		strcpy(conninfo, "dbname=");
		strcat(conninfo, dbnames[i]);
		fprintf(stdout, "%d) %s\n", i + 1, conninfo);

		conns[i] = PQconnectdb(conninfo);
		if (PQstatus(conns[i]) != CONNECTION_OK) {
			fprintf(stderr, "ERROR: %s", PQerrorMessage(conns[i]));
			PQfinish(conns[i]);
			conns[i] = NULL;
		} else {
			fprintf(stdout, "Connected to %s!\n", dbnames[i]);
		}
	}

	fprintf(stdout, "Initializing mutexes:\n");
	locks = malloc(ndbs * sizeof(pthread_mutex_t));
	for (i = 0; i < ndbs; i++) {
		if (pthread_mutex_init(&locks[i], NULL) != 0) {
			fprintf(stderr, "%d) Mutex init failed\n", i + 1);
		} else {
			//fprintf(stdout, "%d) %p\n", i + 1, locks[i]);
		}
	}

	nreqs = MAX_SQL_THREADS;
	//typedef unsigned long int pthread_t;

	fprintf(stdout, "Creating threads:\n");
	threads = malloc(nreqs * ndbs * sizeof(pthread_t));
	//memset(threads, 0, nreqs * ndbs * sizeof(pthread_t));
	for (i = 0; i < ndbs; i++) {
		for (j = 0; j < nreqs; j++) {
			fprintf(stdout, "%d:%d) conn: %p\n", i + 1, j + 1, conns[i]);
			//fprintf(stdout, "%llu\n", &threads[i][j]);
			//threads[i*(nreqs-1)+j-1]);
			ret = pthread_create(&threads[i][j], NULL, run, (void*) i); // FIXME: causing core dump
			fprintf(stdout, "%d) ret = %d\n", i + 1, ret);
		}
	}

	fprintf(stdout, "Joining threads:\n");
	for (i = 0; i < ndbs; i++) {
		for (j = 0; j < nreqs; j++) {
			pthread_join(threads[i][j], NULL);
		}
	}
	free(threads);

	fprintf(stdout, "Destroying mutexes:\n");
	for (i = 0; i < ndbs; i++) {
		//fprintf(stdout, "%d) %p\n", i + 1, locks[i]);
		pthread_mutex_destroy(&locks[i]);
	}
	free(locks);

	// free the connections
	fprintf(stdout, "Releasing connections:\n");
	for (i = 0; i < ndbs; i++) {
		fprintf(stdout, "%d) %p\n", i + 1, conns[i]);
		if (conns[i])
			PQfinish(conns[i]);
	}
	free(conns);

	PQfinish(conn);

	return 0;
}

void *run(void *ptr)
{
	PGconn *conn;
	PGresult *res;
	int index, i;

	fprintf(stdout, "Running thread:\n");

	index = (int)ptr;
	conn = conns[index];

	if (!conn)
		return;

	pthread_mutex_lock(&locks[index]);

	res = PQexec(conn, "\
SELECT c.relname, pg_size_pretty(pg_relation_size(c.oid)) AS size \
FROM pg_class c \
  LEFT JOIN pg_namespace n ON n.oid = c.relnamespace \
WHERE c.relkind IN ('r','') \
  AND n.nspname <> 'pg_catalog' \
  AND n.nspname <> 'information_schema' \
  AND n.nspname !~ '^pg_toast' \
  AND pg_table_is_visible(c.oid) \
  AND pg_sleep(random()) IS NOT NULL \
ORDER BY 1");

	if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		fprintf(stderr, "ERROR: %s\n", PQerrorMessage(conn));
		PQclear(res);
		return;
	}

	for (i = 0; i < PQntuples(res); i++)
		printf("  %s =>\t%s  \t%s\n", dbnames[index],
			PQgetvalue(res, i, 0), PQgetvalue(res, i, 1));

	PQclear(res);

	pthread_mutex_unlock(&locks[index]);
}

