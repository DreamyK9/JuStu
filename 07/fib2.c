#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

unsigned long long int fibs[51] = {0};

unsigned long long int fib(int n);

int main () {
	clock_t start, end;
	unsigned long long int val;
	double time_taken, total_time_taken;

	// print header for output table
	puts("  i  | fibonacci(i) |   time");
	
	// for the numbers 0-50
	for (int i = 0; i <= 50; i++) {
		start = clock(); // Record the starting tick
		
		val = fib(i); // calculate fibonacci of i
		fibs[i] = val;

		end = clock(); // Record the ending tick

		// calculate time taken for the number i
		time_taken = (double)(end - start) / (double)(CLOCKS_PER_SEC);
		total_time_taken += (double)time_taken;
		// print results to the console
		printf("  %2d | %12llu | %8.5lf\n", i, val, time_taken);
	}

	// print total execution time
	printf("\nTotal execution time: %.5f sec", total_time_taken);
	return 0;
}

unsigned long long int fib(int n) {
	if (n == 0 || n == 1) return n;
	else if (fibs[n]) return fibs[n];
	else if (fibs[n-1]) return fibs[n-1] + fibs[n-2];
	else return fib(n-1) + fib(n-2);
}
