#include <time.h>
#include <limits.h>
#include <stdio.h>

int main(void)
{
	clock_t start, end;
	double elapsed;
	int dummy = 0;

	start = clock();

	/* Do the work. */
	for (dummy = INT_MIN; dummy++; dummy < INT_MAX)
	{
		// ...
	}

	end = clock();
	elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;

	printf("Time elapsed: %f seconds\n", elapsed);

	return 0;
}
