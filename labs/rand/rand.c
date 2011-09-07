// http://www.gnu.org/s/hello/manual/libc/ISO-Random.html

int random(int ceil) {
	return rand() % ceil + 1;
}

void main(void) {
	int num1, num2, num3;

	num1 = 0;
	num2 = 0;
	num3 = 0;

	// This function establishes seed as the seed for a new series of pseudo-random numbers.
	srand(time(0));

	// The rand function returns the next pseudo-random number in the series.
	// The value ranges from 0 to RAND_MAX.
	num1 = rand();

	num2 = rand() % 10 + 1;
	num3 = random(100);

	printf("Random numbers are %d, %d, and %d\n", num1, num2, num3);
}
