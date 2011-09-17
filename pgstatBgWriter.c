/**
 * pgstatBgWriter MIB group implementation
 *
 * Note: this file originally auto-generated by mib2c
 */

#include "pgstatmibd.h"
#include "pgstatBgWriter.h"

//#include "util_funcs/header_generic.h"

static oid pgstatBgWriter_oid[] = { 1, 3, 6, 1, 4, 1, 27645, 3, 10 };

struct variable1 pgstatBgWriter_vars[] = {
    {PGSTATBGWRITER_CHECKPOINTSTIMED, 		ASN_COUNTER, RONLY, getvalue, 1, {1}},
    {PGSTATBGWRITER_CHECKPOINTSREQUESTED, 	ASN_COUNTER, RONLY, getvalue, 1, {2}},
    {PGSTATBGWRITER_BUFFERSCHECKPOINT, 		ASN_COUNTER, RONLY, getvalue, 1, {3}},
    {PGSTATBGWRITER_BUFFERSCLEAN, 			ASN_COUNTER, RONLY, getvalue, 1, {4}},
    {PGSTATBGWRITER_MAXWRITTENCLEAN, 		ASN_COUNTER, RONLY, getvalue, 1, {5}},
    {PGSTATBGWRITER_BUFFERSBACKEND, 		ASN_COUNTER, RONLY, getvalue, 1, {6}},
    {PGSTATBGWRITER_BUFFERSALLOCATED, 		ASN_COUNTER, RONLY, getvalue, 1, {7}}
};

void
init_pgstatBgWriter(void)
{
    DEBUGMSGTL((PGSTATBGWRITER_NAME, "Initializing\n"));
    REGISTER_MIB(PGSTATBGWRITER_NAME, pgstatBgWriter_vars, variable1, pgstatBgWriter_oid);
}

static pgstatBgWriterData data;

/**
 * refresh numbers
 */
void
refreshNumbers(void) {

	// TODO: cache these numbers to prevent going to database so frequently

	loadNumbersFromDB();
}

/**
 * load counters from database
 */
void
loadNumbersFromDB(void) {
	PGresult *res;

//    printf("loadNumbersFromDB\n");

	res = PQexec(dbconn, "\
SELECT checkpoints_timed, checkpoints_req, \
	buffers_checkpoint, buffers_clean, \
	maxwritten_clean, buffers_backend, buffers_alloc \
FROM pg_stat_bgwriter");

	if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		// TODO: improve exception handling
		fprintf(stderr, "SELECT command failed: %s", PQerrorMessage(dbconn));
		PQclear(res);
		//exit_nicely(conn);
	}

	data.checkpoints_timed = atoi(PQgetvalue(res, 0, 0));
	data.checkpoints_req = atoi(PQgetvalue(res, 0, 1));
	data.buffers_checkpoint = atoi(PQgetvalue(res, 0, 2));
	data.buffers_clean = atoi(PQgetvalue(res, 0, 3));
	data.maxwritten_clean = atoi(PQgetvalue(res, 0, 4));
	data.buffers_backend = atoi(PQgetvalue(res, 0, 5));
	data.buffers_alloc = atoi(PQgetvalue(res, 0, 6));

	PQclear(res);
}

u_char *
getvalue(struct variable *vp,
            oid * name,
            size_t * length,
            int exact, size_t * var_len, WriteMethod ** write_method)
{

    DEBUGMSGTL((PGSTATBGWRITER_NAME, "getvalue(%d)\n", vp->magic));
//	printf("getvalue(%d)\n", vp->magic);

    if (header_generic(vp, name, length, exact, var_len, write_method) == MATCH_FAILED)
        return NULL;

	// TODO: make a better bound checking routine!
	if (vp->magic >= 1 && vp->magic <= 7)
		refreshNumbers();

    switch (vp->magic) {
    case PGSTATBGWRITER_CHECKPOINTSTIMED:
        return (u_char *) & data.checkpoints_timed;
	case PGSTATBGWRITER_CHECKPOINTSREQUESTED:
        return (u_char *) & data.checkpoints_req;
	case PGSTATBGWRITER_BUFFERSCHECKPOINT:
        return (u_char *) & data.buffers_checkpoint;
	case PGSTATBGWRITER_BUFFERSCLEAN:
        return (u_char *) & data.buffers_clean;
	case PGSTATBGWRITER_MAXWRITTENCLEAN:
        return (u_char *) & data.maxwritten_clean;
	case PGSTATBGWRITER_BUFFERSBACKEND:
        return (u_char *) & data.buffers_backend;
	case PGSTATBGWRITER_BUFFERSALLOCATED:
        return (u_char *) & data.buffers_alloc;
    default:
        DEBUGMSGTL(("snmpd", "unknown sub-id %d in %s\n", vp->magic, PGSTATBGWRITER_NAME));
    }

    return NULL;
}

