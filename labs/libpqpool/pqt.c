#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "libpq-fe.h"
#include <pthread.h>

/* for ntohl/htonl */
#include <netinet/in.h>
#include <arpa/inet.h>

void *run(void *);

PGconn *conn;
pthread_mutex_t lock;

static void
exit_nicely(PGconn *conn)
{
//PQfinish(conn);
}

void *run(void *ptr)
{
	char *message;
	PGresult *res;
	int i;

    pthread_mutex_lock(&lock);

	message = (char *)ptr;
	res = PQexec(conn, "select * from foo limit ceil(random()*10)");

	if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		fprintf(stderr, "select failed: %s\n", PQerrorMessage(conn));
		PQclear(res);
		exit_nicely(conn);
		return;
	}

    for (i = 0; i < PQntuples(res); i++)
        printf("%s: %s\n", message, PQgetvalue(res, i, 0));

	PQclear(res);
	printf("%s completed\n", message);

    pthread_mutex_unlock(&lock);
}

int
main(int argc, char **argv)
{
	const char *conninfo;
	pthread_t thread1, thread2;
	char *message1 = "Thread 1";
	char *message2 = "Thread 2";
	int iret1, iret2;
	PGresult *res;

	conninfo = "dbname=test";

	/* Make a connection to the database */
	conn = PQconnectdb(conninfo);

	/* Check to see that the backend connection was successfully made */
	if (PQstatus(conn) != CONNECTION_OK)
	{
		fprintf(stderr, "Connection to database failed: %s",
		PQerrorMessage(conn));
		exit_nicely(conn);
	}
	else
	{
		fprintf(stderr, "Connected.\n");
	}

	res = PQexec(conn, "\
drop table if exists foo;\
create table foo (id int);\
insert into foo select generate_series(1, 10)");

	if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		fprintf(stderr, "create table failed: %s\n", PQerrorMessage(conn));
		PQclear(res);
		exit_nicely(conn);
		return 1;
	}

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
		PQclear(res);
		exit_nicely(conn);
        return 2;
    }

	iret1 = pthread_create(&thread1, NULL, run, (void*) message1);
	iret2 = pthread_create(&thread2, NULL, run, (void*) message2);

	printf("iret1: %d, iret2: %d\n", iret1, iret2);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

    pthread_mutex_destroy(&lock);

	/* close the connection to the database and cleanup */
	PQfinish(conn);

	return 0;
}
