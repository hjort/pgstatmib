#include "myio.h"

FILE *sopen(char *fpath, char *omode)
{
	FILE *fp;

	if ((fp = fopen(fpath, omode)))
	{
		return fp;
	}
	else
	{
		return NULL;
	}
}

int s2s(FILE * fp, FILE * stream)
{
	int c;

	while ((c = fgetc(fp)) != EOF)
	{
		putc(c, stream);
	}
	return 0;
}

int _sinf_(FILE * fp)
{
	printf("_fileno:%d\n", fp->_fileno);
	printf("_flags2:%d\n", fp->_flags2);
// printf("_blksize:%d\n", fp->_blksize);

/*
printf("_r:%d\n", fp->_r);
printf("_w:%d\n", fp->_w);
printf("_flags:%x\n", fp->_flags);
printf("_file:%x\n", fp->_file);
printf("_lbfsize:%x\n", fp->_lbfsize);
printf("_blksize:%d\n", fp->_blksize);
printf("_offset:%d\n", fp->_offset);
*/
	return 0;
}
