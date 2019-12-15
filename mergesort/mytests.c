
#include <stdio.h>
#include <stdlib.h>


#define TRUE 1
#define FALSE 0
#define THREAD_MAX 8

// function prototypes
int check_if_sorted(int A[], int n);
void generate_random_array(int A[], int n, int seed);
void serial_mergesort(int A[], int p, int r); 
void merge(int A[], int p, int q, int r);
void insertion_sort(int A[], int p, int r);
void parallel_mergesort(int A[], int p, int r, int numthreads);
double getMilliSeconds(void);


/*
 * generate_random_array(int A[], int n, int seed):
 *
 * description: Generate random integers in the range [0,RANGE]
 *              and store in A[1..n]
 */

#define RANGE 1000000

void generate_random_array(int A[], int n, int seed)
{
    int i;

	srandom(seed);
    for (i=1; i<=n; i++)
        A[i] = random()%RANGE;
}


/*
 * check_if_sorted(int A[], int n):
 *
 * description: returns TRUE if A[1..n] are sorted in nondecreasing order
 *              otherwise returns FALSE
 */     

int check_if_sorted(int A[], int n) 
{
	int i=0;

	for (i=1; i<n; i++) {
		if (A[i] > A[i+1]) {
			return FALSE;
		}
	}
	return TRUE;
}




int main(int argc, char **argv) {
	
	if (argc <3) { // there must be at least one command-line argument
			fprintf(stderr, "Usage: %s <input size> <num_threads> [-f <stats to file>] [<seed>] \n", argv[0]);
			exit(1);
	}
	
	int n = atoi(argv[1]);
	int seed = 1;
	// Get the number of threads and make sure it's possitive and greater than zero
	int threads = atoi(argv[2]);
	// Make sure we have a positive number of threads and that we're within our set limit of threads
	if (threads <= 0)
	{
		threads = 1;
	} else if (threads > THREAD_MAX)
	{
		fprintf(stderr, "Please limit the number of threads used to %d\n", THREAD_MAX);
		exit(1);
	}

	int print_file = FALSE;
	// check the rest of the arguments
	if (argc > 3)
	{
		// Get the randomized seed or the -f flag
		if (argc >= 4) {
			if (strmp(argv[3], "-f"))
			{
				print_file = TRUE;
			} else 
			{
				seed = atoi(argv[3]);
			}
		}

		if (argc == 5)
		{
			seed = atoi(argv[4]);
		}
		
	}
		
	int *A = (int *) malloc(sizeof(int) * (n+1)); // n+1 since we are using A[1]..A[n]
		
	// generate random input
	
	generate_random_array(A,n, seed);
	
	double start_time;
	double sorting_time;

	// sort the input (and time it)
	start_time = getMilliSeconds();
	
	// Everything will now pass through the parallel sort
	parallel_mergesort(A, 1, n, threads);

	sorting_time = getMilliSeconds() - start_time;
	
	// print results if correctly sorted otherwise cry foul and exit
	if (check_if_sorted(A,n)) {
		printf("Sorting %d elements took %4.2lf seconds.\n", n,  sorting_time/1000.0);
	} else { 
		printf("%s: sorting failed!!!!\n", argv[0]);
		// I still wanted to be able to see how long failures took to process
		printf("Processing %d elements took %4.2lf seconds.\n", n,  sorting_time/1000.0);
		exit(EXIT_FAILURE);
	}

	// Writing to file, not the best method at the moment
	if (print_file)
	{
		FILE *fp;
		char filename[1024];
		snprintf(filename, sizeof(filename), "sortStats_%dt.csv", threads);

		fp = fopen(filename, "a+");
		fprintf(fp, "%d, %d, %4.2lf\n", threads, n, sorting_time/1000.0);
		fputs("Finished writing to csv\n", fp);
		fclose(fp);
		printf("Finished writing to %s", filename);
	}	

	exit(EXIT_SUCCESS); 
} 
