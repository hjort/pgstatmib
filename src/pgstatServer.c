/*
 * pgstatServer MIB group implementation
 *
 * Note: this file originally auto-generated by mib2c
 */

#include "pgstatmibd.h"
#include "pgstatServer.h"

static oid pgstatServer_oid[] = { 1, 3, 6, 1, 4, 1, 27645, 3, 1 };

struct variable1 pgstatServer_vars[] = {
    {PGSTATSERVER_DATABASECOUNT, 	ASN_INTEGER, RONLY, getvalue_pgstatServer, 1, {1}},
    {PGSTATSERVER_SIZE, 			ASN_UNSIGNED, RONLY, getvalue_pgstatServer, 1, {2}},
    {PGSTATSERVER_BACKENDS, 		ASN_GAUGE, RONLY, getvalue_pgstatServer, 1, {3}},
    {PGSTATSERVER_COMMITS, 			ASN_COUNTER, RONLY, getvalue_pgstatServer, 1, {4}},
    {PGSTATSERVER_ROLLBACKS, 		ASN_COUNTER, RONLY, getvalue_pgstatServer, 1, {5}},
    {PGSTATSERVER_BLOCKSREAD, 		ASN_COUNTER, RONLY, getvalue_pgstatServer, 1, {6}},
    {PGSTATSERVER_BLOCKSHIT, 		ASN_COUNTER, RONLY, getvalue_pgstatServer, 1, {7}},
    {PGSTATSERVER_ROLLBACKRATIO, 	ASN_UNSIGNED, RONLY, getvalue_pgstatServer, 1, {8}},
    {PGSTATSERVER_CACHEHITRATIO, 	ASN_UNSIGNED, RONLY, getvalue_pgstatServer, 1, {9}}
};

void
init_pgstatServer(void)
{
    DEBUGMSGTL((PGSTATSERVER_NAME, "Initializing\n"));
    REGISTER_MIB(PGSTATSERVER_NAME, pgstatServer_vars, variable1, pgstatServer_oid);
}

static pgstatServerData pgstatServer_data;

/**
 * refresh numbers
 */
void
refresh_numbers_pgstatServer(void) {
	time_t now;
	unsigned int diff;

	// use cache on these numbers to prevent going to database so frequently
	now = time (NULL);
	diff = (now - pgstatServer_data.last_load);

	if (pgstatServer_data.last_load == 0 || diff >= PGSTATSERVER_CACHE_TIMEOUT) {
		load_numbers_from_db_pgstatServer();
		pgstatServer_data.last_load = now;
	}
}

/**
 * load counters from database
 */
void
load_numbers_from_db_pgstatServer(void) {
	PGresult *res;

    DEBUGMSGTL((PGSTATSERVER_NAME, "Loading numbers from DB\n"));

	res = PQexec(dbconn, "\
SELECT count(datid) as database_count, \
	sum(pg_database_size(datid)) as total_size, sum(numbackends) as total_backends, \
	sum(xact_commit) as total_commits, sum(xact_rollback) as total_rollbacks, \
	sum(blks_read) as total_blks_read, sum(blks_hit) as total_blks_hit, \
	(sum(xact_rollback) / sum(xact_commit + xact_rollback) * 1e4)::int as rollback_ratio, \
	(sum(blks_hit) / sum(blks_read + blks_hit) * 1e4)::int as cache_hit_ratio \
FROM pg_stat_database");

	if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		// TODO: improve exception handling
		fprintf(stderr, "SELECT command failed: %s", PQerrorMessage(dbconn));
		PQclear(res);
		//exit_nicely(conn);
	}

	pgstatServer_data.database_count = atoi(PQgetvalue(res, 0, 0));
	pgstatServer_data.total_size = atoi(PQgetvalue(res, 0, 1));
	pgstatServer_data.total_backends = atoi(PQgetvalue(res, 0, 2));
	pgstatServer_data.total_commits = atoi(PQgetvalue(res, 0, 3));
	pgstatServer_data.total_rollbacks = atoi(PQgetvalue(res, 0, 4));
	pgstatServer_data.total_blks_read = atoi(PQgetvalue(res, 0, 5));
	pgstatServer_data.total_blks_hit = atoi(PQgetvalue(res, 0, 6));
	pgstatServer_data.rollback_ratio = atoi(PQgetvalue(res, 0, 7));
	pgstatServer_data.cache_hit_ratio = atoi(PQgetvalue(res, 0, 8));

	PQclear(res);
}

u_char  *
getvalue_pgstatServer(struct variable *vp,
            oid * name,
            size_t * length,
            int exact, size_t * var_len, WriteMethod ** write_method)
{
    DEBUGMSGTL((PGSTATSERVER_NAME, "getvalue(%d)\n", vp->magic));

    if (header_generic(vp, name, length, exact, var_len, write_method) == MATCH_FAILED)
        return NULL;

	if (vp->magic >= PGSTATSERVER_FIRST && vp->magic <= PGSTATSERVER_LAST)
		refresh_numbers_pgstatServer();

    switch (vp->magic) {
    case PGSTATSERVER_DATABASECOUNT:
        return (u_char *) & pgstatServer_data.database_count;
    case PGSTATSERVER_SIZE:
        return (u_char *) & pgstatServer_data.total_size;
    case PGSTATSERVER_BACKENDS:
        return (u_char *) & pgstatServer_data.total_backends;
    case PGSTATSERVER_COMMITS:
        return (u_char *) & pgstatServer_data.total_commits;
    case PGSTATSERVER_ROLLBACKS:
        return (u_char *) & pgstatServer_data.total_rollbacks;
    case PGSTATSERVER_BLOCKSREAD:
        return (u_char *) & pgstatServer_data.total_blks_read;
    case PGSTATSERVER_BLOCKSHIT:
        return (u_char *) & pgstatServer_data.total_blks_hit;
    case PGSTATSERVER_ROLLBACKRATIO:
        return (u_char *) & pgstatServer_data.rollback_ratio;
    case PGSTATSERVER_CACHEHITRATIO:
        return (u_char *) & pgstatServer_data.cache_hit_ratio;
    default:
        DEBUGMSGTL(("snmpd", "unknown sub-id %d in %s\n", vp->magic, PGSTATSERVER_NAME));
    }
    return NULL;
}

