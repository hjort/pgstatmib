/*
 * Note: this file originally auto-generated by mib2c
 */

#include "pgstatmibd.h"
#include "pgstatDatabaseTable.h"

/** Initialize the pgstatDatabaseTable table by defining its contents and how it's structured */
void
initialize_table_pgstatDatabaseTable(void)
{
    const oid pgstatDatabaseTable_oid[] = {1,3,6,1,4,1,27645,3,1};
    netsnmp_table_data_set *table_set;
    netsnmp_table_row *row;

//enum { COL3 = 2, COL4 = 3, COL5 = 4, };
//int32_t ival;
//int32_t i, j;

    int32_t datid;//, ival;

    // TODO: get this out of here (perhaps on a struct?)
    PGresult *res;
    int i;
    char *datname;
    int32_t numbackends, rollback_ratio, cache_hit_ratio;
    u_long xact_commit, xact_rollback, blks_read, blks_hit;
    u_long tup_returned, tup_fetched, tup_inserted, tup_updated, tup_deleted, tup_modified;

    /* create the table structure itself */
    table_set = netsnmp_create_table_data_set("pgstatDatabaseTable");

    /* comment this out or delete if you don't support creation of new rows */
    //table_set->allow_creation = 1;

    /***************************************************
     * Adding indexes
     */
    DEBUGMSGTL(("initialize_table_pgstatDatabaseTable",
                "adding indexes to table pgstatDatabaseTable\n"));
    netsnmp_table_set_add_indexes(table_set,
                           ASN_INTEGER,  // index: PGSTATDATABASEID
                           0);
//netsnmp_table_dataset_add_index(table_set, ASN_INTEGER);

    DEBUGMSGTL(("initialize_table_pgstatDatabaseTable",
                "adding column types to table pgstatDatabaseTable\n"));		 
    netsnmp_table_set_multi_add_default_row(table_set,
            COLUMN_PGSTATDATABASEID, ASN_INTEGER, 0, NULL, 0,
            COLUMN_PGSTATDATABASENAME, ASN_OCTET_STR, 0, NULL, 0,
            COLUMN_PGSTATDATABASEBACKENDS, ASN_GAUGE, 0, NULL, 0,
            COLUMN_PGSTATDATABASECOMMITS, ASN_COUNTER, 0, NULL, 0,
            COLUMN_PGSTATDATABASEROLLBACKS, ASN_COUNTER, 0, NULL, 0,
            COLUMN_PGSTATDATABASEBLOCKSREAD, ASN_COUNTER, 0, NULL, 0,
            COLUMN_PGSTATDATABASEBLOCKSHIT, ASN_COUNTER, 0, NULL, 0,
            COLUMN_PGSTATDATABASETUPLESRETURNED, ASN_COUNTER, 0, NULL, 0,
            COLUMN_PGSTATDATABASETUPLESFETCHED, ASN_COUNTER, 0, NULL, 0,
            COLUMN_PGSTATDATABASETUPLESINSERTED, ASN_COUNTER, 0, NULL, 0,
            COLUMN_PGSTATDATABASETUPLESUPDATED, ASN_COUNTER, 0, NULL, 0,
            COLUMN_PGSTATDATABASETUPLESDELETED, ASN_COUNTER, 0, NULL, 0,
            COLUMN_PGSTATDATABASEROLLBACKRATIO, ASN_UNSIGNED, 0, NULL, 0,
            COLUMN_PGSTATDATABASECACHEHITRATIO, ASN_UNSIGNED, 0, NULL, 0,
            COLUMN_PGSTATDATABASETUPLESMODIFIED, ASN_COUNTER, 0, NULL, 0,
	    0);

/*netsnmp_table_set_add_default_row(table_set, COL3, ASN_INTEGER,   FALSE, NULL, 0);
netsnmp_table_set_add_default_row(table_set, COL4, ASN_COUNTER,   FALSE, NULL, 0);
netsnmp_table_set_add_default_row(table_set, COL5, ASN_OCTET_STR, FALSE, NULL, 0);*/
    
    /* registering the table with the master agent */
    /* note: if you don't need a subhandler to deal with any aspects
       of the request, change pgstatDatabaseTable_handler to "NULL" */
    netsnmp_register_table_data_set(netsnmp_create_handler_registration("pgstatDatabaseTable", pgstatDatabaseTable_handler,
                                                        pgstatDatabaseTable_oid,
                                                        OID_LENGTH(pgstatDatabaseTable_oid),
                                                        HANDLER_CAN_RWRITE),
                            table_set, NULL);

    /*
     * create the a row for the table, add the data, and add the row to the table 
     */

/*
$ snmpwalk localhost pgstatDatabase
PGSTAT-MIB::pgstatDatabaseId.11874 = INTEGER: 11874
PGSTAT-MIB::pgstatDatabaseId.16448 = INTEGER: 16448
PGSTAT-MIB::pgstatDatabaseName.11874 = STRING: postgres
PGSTAT-MIB::pgstatDatabaseName.16448 = STRING: rodrigo
PGSTAT-MIB::pgstatDatabaseBackends.11874 = Gauge32: 200
PGSTAT-MIB::pgstatDatabaseBackends.16448 = Gauge32: 10
PGSTAT-MIB::pgstatDatabaseCommits.11874 = Counter32: 50000
PGSTAT-MIB::pgstatDatabaseCommits.16448 = Counter32: 25000
PGSTAT-MIB::pgstatDatabaseRollbacks.11874 = Counter32: 100
PGSTAT-MIB::pgstatDatabaseRollbacks.16448 = Counter32: 50
*/

	// FIMXE: move this code out of here!
	res = PQexec(dbconn, "\
SELECT datid, datname, numbackends, xact_commit, xact_rollback, blks_read, blks_hit, \
	tup_returned, tup_fetched, tup_inserted, tup_updated, tup_deleted, \
	(xact_rollback::numeric / (xact_commit + xact_rollback + 1e-5) * 1e4)::int as rollback_ratio, \
	(blks_hit::numeric / (blks_hit + blks_read + 1e-5) * 1e4)::int as cache_hit_ratio, \
	(tup_inserted + tup_updated + tup_deleted) as tup_modified \
FROM pg_stat_database \
WHERE datname !~ '^template' \
ORDER BY datid");

	if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		fprintf(stderr, "SELECT command failed: %s", PQerrorMessage(dbconn));
		PQclear(res);
		//exit_nicely(conn);
	}

	for (i = 0; i < PQntuples(res); i++)
	{
		row = netsnmp_create_table_data_row();

		datid = atoi(PQgetvalue(res, i, 0));
		netsnmp_table_row_add_index(row, ASN_INTEGER, &datid, sizeof(datid));
		netsnmp_table_dataset_add_row(table_set, row);
		netsnmp_set_row_column(row, COLUMN_PGSTATDATABASEID, ASN_INTEGER, &datid, sizeof(datid));

		datname = PQgetvalue(res, i, 1);
		netsnmp_set_row_column(row, COLUMN_PGSTATDATABASENAME, ASN_OCTET_STR, datname, strlen(datname));

		numbackends = atoi(PQgetvalue(res, i, 2));
		netsnmp_set_row_column(row, COLUMN_PGSTATDATABASEBACKENDS, ASN_GAUGE, &numbackends, sizeof(numbackends));

		xact_commit = atoi(PQgetvalue(res, i, 3));
		netsnmp_set_row_column(row, COLUMN_PGSTATDATABASECOMMITS, ASN_COUNTER, &xact_commit, sizeof(xact_commit));

		xact_rollback = atoi(PQgetvalue(res, i, 4));
		netsnmp_set_row_column(row, COLUMN_PGSTATDATABASEROLLBACKS, ASN_COUNTER, &xact_rollback, sizeof(xact_rollback));

		blks_read = atoi(PQgetvalue(res, i, 5));
		netsnmp_set_row_column(row, COLUMN_PGSTATDATABASEBLOCKSREAD, ASN_COUNTER, &blks_read, sizeof(blks_read));

		blks_hit = atoi(PQgetvalue(res, i, 6));
		netsnmp_set_row_column(row, COLUMN_PGSTATDATABASEBLOCKSHIT, ASN_COUNTER, &blks_hit, sizeof(blks_hit));

		tup_returned = atoi(PQgetvalue(res, i, 7));
		netsnmp_set_row_column(row, COLUMN_PGSTATDATABASETUPLESRETURNED, ASN_COUNTER, &tup_returned, sizeof(tup_returned));

		tup_fetched = atoi(PQgetvalue(res, i, 8));
		netsnmp_set_row_column(row, COLUMN_PGSTATDATABASETUPLESFETCHED, ASN_COUNTER, &tup_fetched, sizeof(tup_fetched));

		tup_inserted = atoi(PQgetvalue(res, i, 9));
		netsnmp_set_row_column(row, COLUMN_PGSTATDATABASETUPLESINSERTED, ASN_COUNTER, &tup_inserted, sizeof(tup_inserted));

		tup_updated = atoi(PQgetvalue(res, i, 10));
		netsnmp_set_row_column(row, COLUMN_PGSTATDATABASETUPLESUPDATED, ASN_COUNTER, &tup_updated, sizeof(tup_updated));

		tup_deleted = atoi(PQgetvalue(res, i, 11));
		netsnmp_set_row_column(row, COLUMN_PGSTATDATABASETUPLESDELETED, ASN_COUNTER, &tup_deleted, sizeof(tup_deleted));

		rollback_ratio = atoi(PQgetvalue(res, i, 12));
		netsnmp_set_row_column(row, COLUMN_PGSTATDATABASEROLLBACKRATIO, ASN_UNSIGNED, &rollback_ratio, sizeof(rollback_ratio));

		cache_hit_ratio = atoi(PQgetvalue(res, i, 13));
		netsnmp_set_row_column(row, COLUMN_PGSTATDATABASECACHEHITRATIO, ASN_UNSIGNED, &cache_hit_ratio, sizeof(cache_hit_ratio));

		tup_modified = atoi(PQgetvalue(res, i, 14));
		netsnmp_set_row_column(row, COLUMN_PGSTATDATABASETUPLESMODIFIED, ASN_COUNTER, &tup_modified, sizeof(tup_modified));
	}

	PQclear(res);
	// ...

	/*
	// row 1
        row = netsnmp_create_table_data_row();
	datid = 11874;
	netsnmp_table_row_add_index(row, ASN_INTEGER, &datid, sizeof(datid));
	netsnmp_table_dataset_add_row(table_set, row);
	netsnmp_set_row_column(row, COLUMN_PGSTATDATABASEID, ASN_INTEGER, &datid, sizeof(datid));
	netsnmp_set_row_column(row, COLUMN_PGSTATDATABASENAME, ASN_OCTET_STR, "postgres", strlen("postgres"));
	ival = 200;
	netsnmp_set_row_column(row, COLUMN_PGSTATDATABASEBACKENDS, ASN_GAUGE, &ival, sizeof(ival));
	ival = 50000;
	netsnmp_set_row_column(row, COLUMN_PGSTATDATABASECOMMITS, ASN_COUNTER, &ival, sizeof(ival));
	ival = 100;
	netsnmp_set_row_column(row, COLUMN_PGSTATDATABASEROLLBACKS, ASN_COUNTER, &ival, sizeof(ival));
	//...
	ival = 15;
	netsnmp_set_row_column(row, COLUMN_PGSTATDATABASEROLLBACKRATIO, ASN_UNSIGNED, &ival, sizeof(ival));
	ival = 9775;
	netsnmp_set_row_column(row, COLUMN_PGSTATDATABASECACHEHITRATIO, ASN_UNSIGNED, &ival, sizeof(ival));
	ival = 20000;
	netsnmp_set_row_column(row, COLUMN_PGSTATDATABASETUPLESMODIFIED, ASN_COUNTER, &ival, sizeof(ival));

	// row 2
        row = netsnmp_create_table_data_row();
	datid = 16448;
	netsnmp_table_row_add_index(row, ASN_INTEGER, &datid, sizeof(datid));
	netsnmp_table_dataset_add_row(table_set, row);
	netsnmp_set_row_column(row, COLUMN_PGSTATDATABASEID, ASN_INTEGER, &datid, sizeof(datid));
	netsnmp_set_row_column(row, COLUMN_PGSTATDATABASENAME, ASN_OCTET_STR, "rodrigo", strlen("rodrigo"));
	ival = 10;
	netsnmp_set_row_column(row, COLUMN_PGSTATDATABASEBACKENDS, ASN_GAUGE, &ival, sizeof(ival));
	ival = 25000;
	netsnmp_set_row_column(row, COLUMN_PGSTATDATABASECOMMITS, ASN_COUNTER, &ival, sizeof(ival));
	ival = 50;
	netsnmp_set_row_column(row, COLUMN_PGSTATDATABASEROLLBACKS, ASN_COUNTER, &ival, sizeof(ival));
	//...
	ival = 5;
	netsnmp_set_row_column(row, COLUMN_PGSTATDATABASEROLLBACKRATIO, ASN_UNSIGNED, &ival, sizeof(ival));
	ival = 8920;
	netsnmp_set_row_column(row, COLUMN_PGSTATDATABASECACHEHITRATIO, ASN_UNSIGNED, &ival, sizeof(ival));
	ival = 3000;
	netsnmp_set_row_column(row, COLUMN_PGSTATDATABASETUPLESMODIFIED, ASN_COUNTER, &ival, sizeof(ival));
	*/

	/*for (i = 1; i <= 2; i++) {
	    for (j = 1; j <= 2; j++) {
		row = netsnmp_create_table_data_row();
		netsnmp_table_row_add_index(row, ASN_INTEGER, &i, sizeof(i));
		netsnmp_table_row_add_index(row, ASN_INTEGER, &j, sizeof(j));
		netsnmp_table_dataset_add_row(table_set, row);

		ival = 10 * i + j;
		netsnmp_set_row_column(row, COL3, ASN_INTEGER, &ival, sizeof(ival));
		netsnmp_set_row_column(row, COL5, ASN_OCTET_STR, "test", sizeof("test") - 1);
	    }
	}*/

}

/** Initializes the pgstatDatabaseTable module */
void
init_pgstatDatabaseTable(void)
{

  /* here we initialize all the tables we're planning on supporting */
    initialize_table_pgstatDatabaseTable();
}

/** handles requests for the pgstatDatabaseTable table, if anything else needs to be done */
int
pgstatDatabaseTable_handler(
    netsnmp_mib_handler               *handler,
    netsnmp_handler_registration      *reginfo,
    netsnmp_agent_request_info        *reqinfo,
    netsnmp_request_info              *requests) {
    /* perform anything here that you need to do.  The requests have
       already been processed by the master table_dataset handler, but
       this gives you chance to act on the request in some other way
       if need be. */
    return SNMP_ERR_NOERROR;
}
