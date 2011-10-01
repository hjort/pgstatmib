#include <unistd.h>
#include <stdio.h>

int main(void)
{
	unsigned int secs = 5;

	printf("Sleeping for %d seconds...\n", secs);

	sleep(secs);

	printf("Just woke up!\n");

	return 0;
}

