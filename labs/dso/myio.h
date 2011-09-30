#include <stdio.h>

/*
opens stream
@param fpath, omode - path to file, file open mode
@return fp or NULL
*/
FILE *sopen(char *fpath, char *omode);

/*
copy file to file, stream to stream
@param fp, stream
@return 0
*/
int s2s(FILE * fp, FILE * stream);

/*
get info from FILE struct, prints it to stdout
@param FILE *fp
@return 0;
*/
int _sinf_(FILE * fp);
