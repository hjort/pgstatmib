#include <time.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	time_t start, finish;
	double diff;

	start = time(NULL);
	sleep(5);
	finish = time(NULL);

	diff = difftime(finish, start);

	printf("Time difference: %f s\n", diff);

	return 0;
}

