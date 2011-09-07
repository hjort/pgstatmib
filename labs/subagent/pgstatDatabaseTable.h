/*
 * Note: this file originally auto-generated by mib2c using
 *  $
 */
#ifndef PGSTATDATABASETABLE_H
#define PGSTATDATABASETABLE_H

/* function declarations */
void init_pgstatDatabaseTable(void);
void initialize_table_pgstatDatabaseTable(void);
Netsnmp_Node_Handler pgstatDatabaseTable_handler;

/* column number definitions for table pgstatDatabaseTable */
       #define COLUMN_PGSTATDATABASEINDEX		1
       #define COLUMN_PGSTATDATABASENAME		2
       #define COLUMN_PGSTATDATABASEBACKENDS		3
       #define COLUMN_PGSTATDATABASECOMMITS		4
       #define COLUMN_PGSTATDATABASEROLLBACKS		5
       #define COLUMN_PGSTATDATABASEBLOCKSREAD		6
       #define COLUMN_PGSTATDATABASEBLOCKSHIT		7
       #define COLUMN_PGSTATDATABASETUPLESRETURNED		8
       #define COLUMN_PGSTATDATABASETUPLESFETCHED		9
       #define COLUMN_PGSTATDATABASETUPLESINSERTED		10
       #define COLUMN_PGSTATDATABASETUPLESUPDATED		11
       #define COLUMN_PGSTATDATABASETUPLESDELETED		12
       #define COLUMN_PGSTATDATABASEROLLBACKRATIO		21
       #define COLUMN_PGSTATDATABASECACHEHITRATIO		22
       #define COLUMN_PGSTATDATABASETUPLESMODIFIED		23
#endif /* PGSTATDATABASETABLE_H */
