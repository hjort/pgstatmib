/*
 * pgstatBgWriter MIB group interface
 *
 * Note: this file originally auto-generated by mib2c
 */
#ifndef PGSTATBGWRITER_H
#define PGSTATBGWRITER_H

/* module name */
#define PGSTATBGWRITER_NAME	"pgstatBgWriter"

//config_require(util_funcs/header_generic)

/* function declarations */
void init_pgstatBgWriter(void);
void refreshNumbers(void);
void loadNumbersFromDB(void);
FindVarMethod getvalue;

/* scalar number definitions for pgstatBgWriter */
#define PGSTATBGWRITER_CHECKPOINTSTIMED			1
#define PGSTATBGWRITER_CHECKPOINTSREQUESTED		2
#define PGSTATBGWRITER_BUFFERSCHECKPOINT		3
#define PGSTATBGWRITER_BUFFERSCLEAN				4
#define PGSTATBGWRITER_MAXWRITTENCLEAN			5
#define PGSTATBGWRITER_BUFFERSBACKEND			6
#define PGSTATBGWRITER_BUFFERSALLOCATED			7

#endif /* PGSTATBGWRITER_H */
