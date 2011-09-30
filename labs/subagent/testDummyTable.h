#ifndef TESTDUMMYTABLE_H
#define TESTDUMMYTABLE_H

config_require(host/data_access/swinst)

/*
 * function declarations 
 */
void init_testDummyTable(void);
void shutdown_testDummyTable(void);
void initialize_table_testDummyTable(void);
Netsnmp_Node_Handler testDummyTable_handler;

/*
 * column number definitions for table testDummyTable
 */
#define COLUMN_TESTDUMMYINDEX		1
#define COLUMN_TESTDUMMYNAME		2
#define COLUMN_TESTDUMMYID			3
#define COLUMN_TESTDUMMYTYPE		4
#define COLUMN_TESTDUMMYDATE		5

#endif	/* TESTDUMMYTABLE_H */
