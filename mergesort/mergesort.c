

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>


#define TRUE 1
#define FALSE 0
#define THREAD_MAX 4

// function prototypes
void serial_mergesort(int A[], int p, int r); 
void merge(int A[], int p, int q, int r);
void insertion_sort(int A[], int p, int r);
void parallel_mergesort(int A[], int p, int r, int numthreads);

const int INSERTION_SORT_THRESHOLD = 100; //based on trial and error

// struct for pthread_create parameters
struct thread_args {
	int *threadA;
	int threadP;
	int threadR;
};

struct thread_args parallel_args[THREAD_MAX];

/*
 * insertion_sort(int A[], int p, int r):
 *
 * description: Sort the section of the array A[p..r].
 */
void insertion_sort(int A[], int p, int r) 
{
	int j;

	for (j=p+1; j<=r; j++) {
		int key = A[j];
		int i = j-1;
		while ((i > p-1) && (A[i] > key)) {	
			A[i+1] = A[i];
			i--;
		}
		A[i+1] = key;
	}
}

		

/*
 * serial_mergesort(int A[], int p, int r):
 *
 * description: Sort the section of the array A[p..r].
 */
void serial_mergesort(int A[], int p, int r) 
{
	if (r-p+1 <= INSERTION_SORT_THRESHOLD)  {
			insertion_sort(A,p,r);
	} else {
		int q =  r + (p - r)/2;
		serial_mergesort(A, p, q);
		serial_mergesort(A, q+1, r);
		merge(A, p, q, r);
	}
}

void* parallel_serial_sort(void *args) {
	struct thread_args *t_args = (struct thread_args *) args;

	int *t_A = t_args->threadA;
	int t_p = t_args->threadP;
	int t_r = t_args->threadR;

	serial_mergesort(t_A, t_p, t_r);	
	pthread_exit(NULL);
}

/*
 * parallel_mergesort(int A[], int p, int r):
 * 
 * description: Sorts the section of the array A[p...r] 
 * 				using a multi-threaded approach. 
 */
void parallel_mergesort(int A[], int p, int r, int numthreads) {
	pthread_t thread[numthreads];
	int *low;
	int *mid;
	int *high;
	int i, j;

	// Determining how to proceed based on thread count
	switch (numthreads)
	{
	case 1:
		serial_mergesort(A, p, r);
		break;
	case 2:
		*low = (int *) malloc(sizeof(int) * (numthreads/2)+1);
		*high = (int *) malloc(sizeof(int) * (numthreads/2)+1);

		// Fill up each half of the array accordingly
		for (j = p; j < r/2; j++)
		{
			low[j] = A[j];
			high[j] = A[j+(r/2)];
		}
		
		// Filling out each half's arguments 
		parallel_args[0].threadA = low;
		parallel_args[0].threadP = p;
		parallel_args[0].threadR = r/2;

		parallel_args[1].threadA = high;
		parallel_args[1].threadP = p;
		parallel_args[1].threadR = r/2;
	default:
		break;
	}

	// Creating threads
	for (i = 0; i < numthreads; i++)
	{
		pthread_create(&thread[i], NULL, parallel_serial_sort, (void *) &parallel_args[i]);
	}
	
	// Joining the threads
	for (i = 0; i < numthreads; i++)
	{
		pthread_join(thread[i], NULL);
	}

	// // Merge the last parts, determined by numthreads used
	// switch (numthreads)
	// {
	// case 1:
	// 	// This case should've already merged its stuff just break
	// 	break;
	// case 2:
	// 	merge
	// default:
	// 	break;
	// }
	
}

/*
 * merge(int A[], int p, int q, int r):
 *
 * description: Merge two sorted sequences A[p..q] and A[q+1..r] 
 *              and place merged output back in array A. Uses extra
 *              space proportional to A[p..r].
 */     
void merge(int A[], int p, int q, int r) 
{
	int *B = (int *) malloc(sizeof(int) * (r-p+1));
		
	int i = p;
	int j = q+1;
	int k = 0;
	int l;
		
	// as long as both lists have unexamined elements
	// this loop keeps executing.
	while ((i <= q) && (j <= r)) {
		if (A[i] < A[j]) {
			B[k] = A[i];
			i++;
		} else {
			B[k] = A[j];
			j++;
		}
		k++;
	}
		
	// now only at most one list has unprocessed elements.
		
	if (i <= q) { 
		// copy remaining elements from the first list
		for (l=i; l<=q; l++) {
			B[k] = A[l];
			k++;
		}
	} else {
		// copy remaining elements from the second list
		for (l=j; l<=r; l++) {
			B[k] = A[l];
			k++;
		}
	}
		
	// copy merged output from array B back to array A
	k=0;
	for (l=p; l<=r; l++) {
		A[l] = B[k];
		k++;
	}

	free(B);
}

