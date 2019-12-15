
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>


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
void create_csv(char *filename, int threads, int elements, double time);


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
			fprintf(stderr, "Usage: %s <input size> <num_threads> [<seed>] [-f <print file>] \n", argv[0]);
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
	
	// Get the randomized seed
	int print_file = FALSE;
	if (argc == 4) {
		if (argv[3] == "-f") 
		{
			print_file = TRUE;
		} else {
			seed = atoi(argv[2]);
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

	if (print_file) 
	{
		
	}
	

	exit(EXIT_SUCCESS); 
} 

void create_csv(char *filename, int threads, int elements, double time){
 
printf("\n Creating %s.csv file",filename);
 
FILE *fp;
 
int i,j;

struct stat stat_record;

filename=strcat(filename,".csv");

fp=fopen(filename,"w+");
     
if(stat(fp, &stat_record)){
	printf("%s", strerror(errno));
} else if(stat_record.st_size <= 1) {
	fprintf(fp,"Thread Count, Element Count, Time");
	fprintf(fp, "%d, %d, %d\n", threads, elements, time);
} else {
	fprintf(fp, "%d, %d, %d\n", threads, elements, time);
}
 
fclose(fp);
 
printf("\n %sfile written",filename);
 
}
