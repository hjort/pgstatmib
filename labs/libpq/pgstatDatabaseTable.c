#include <stdio.h>
#include <stdlib.h>
#include "libpq-fe.h"

static void
exit_nicely(PGconn *conn)
{
	PQfinish(conn);
	exit(1);
}

int
main(int argc, char **argv)
{
	const char *conninfo;
	PGconn	   *conn;
	PGresult   *res;
	int			nFields;
	int			i,
				j;

	const char* suffixes[] =
	{
		"Index", "Name", "Backends",
		"Commits", "Rollbacks",
		"BlocksRead", "BlocksHit",
		"TuplesReturned", "TuplesFetched",
		"TuplesInserted", "TuplesUpdated", "TuplesDeleted",
		"RollbackRatio", "CacheHitRatio", "TuplesModified"
	};

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
	conn = PQconnectdb(conninfo);

	/* Check to see that the backend connection was successfully made */
	if (PQstatus(conn) != CONNECTION_OK)
	{
		fprintf(stderr, "Connection to database failed: %s",
				PQerrorMessage(conn));
		exit_nicely(conn);
	}

	// ...
	res = PQexec(conn, "\
SELECT datid, datname, numbackends, xact_commit, xact_rollback, blks_read, blks_hit, \
	tup_returned, tup_fetched, tup_inserted, tup_updated, tup_deleted, \
	trunc(xact_rollback::numeric / (xact_commit + xact_rollback) * 100, 4) as rollback_ratio, \
	trunc(blks_hit::numeric / (blks_hit + blks_read) * 100, 4) as cache_hit_ratio, \
	(tup_inserted + tup_updated + tup_deleted) as tup_modified \
FROM pg_stat_database \
WHERE datname !~ '^template' \
ORDER BY datid");
	printf("tuples: %d\n", PQntuples(res));
	if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		fprintf(stderr, "SELECT command failed: %s", PQerrorMessage(conn));
		PQclear(res);
		exit_nicely(conn);
	}

	printf("\n");
	nFields = PQnfields(res);
	for (i = 0; i < PQntuples(res); i++)
	{
		for (j = 0; j < nFields; j++)
			printf("pgstatDatabase%s.%d = %s\n", suffixes[j], i + 1, PQgetvalue(res, i, j));
		printf("\n");
	}

	PQclear(res);

	/* close the connection to the database and cleanup */
	PQfinish(conn);

	return 0;
}
