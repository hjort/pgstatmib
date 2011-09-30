#include "myio.h"

// usage: [./fmgmt hello.txt]
int main(int argc, char **argv, char **environ)
{
	FILE *fp;

	char *mode = "r";

	if (argv[2])
	{
		printf("%s\n", "usage: [./fmgmt hello.txt]");
		return 1;
	}
	else
	{
		if ((fp = sopen(argv[1], mode)))
		{
			printf("%s %s\n", argv[1], "opened!");
			s2s(fp, stdout);
			_sinf_(fp);
			fclose(fp);
		}
		else
		{
			printf("%s %s\n", argv[1], "failed!");
			return 2;
		}
	}
	return 0;
}
