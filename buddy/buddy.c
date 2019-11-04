#include <stdio.h>
#include <math.h>
#include <sys/mman.h>
#include "buddy.h"

/* supports memory upto 2^(MAX_KVAL-1) (or 64 GB) in size */
#define  MAX_KVAL  37

// Declare helper function prototypes
int log_two(size_t size);
int next_best_two(size_t size);
void mem_error(void);

/* the header for an available block */
struct block_header {
	short tag; // This should be 0 if the block is reserved, 1 if the block is available
	short kval; // This is the size of our block (i.e. k)

	// We can assume that these next two structs are for determining who's the next/prev nodes
	struct block_header *next; 
	struct block_header *prev;
};


/* A static structure stores the table of pointers to the lists in the buddy system.  */
struct pool {
	void *start; // pointer to the start of the memory pool
	int lgsize;  // log2 of size
	size_t size; // size of the pool, same as 2 ^ lgsize
	/* the table of pointers to the buddy system lists */
	struct block_header avail[MAX_KVAL];
} pool;

// Pointer for list of buddy lists
struct block_header *availPtr;

/*
 * Public Methods 
 */

/**
 * Buddy Initializer - should be called either by itself or by other functions.
 * @param size - the size for the chunk of memory we want to use
 * @return TRUE - if the setup went according to what was needed
 * 		   ENOMEM - if there was an error in this part
 */
int buddy_init(size_t size) 
{ 
	struct pool mem_pool;

	// Make sure that our size isn't zero and that we don't go over our max
	if (size == 0 || size < (1<<29)) {
		mem_pool.start = mmap(NULL, (1<<29), PROT_READ|PROT_WRITE, MAP_SHARED, ,); // Set our start point for our pool
		mem_pool.size = 1<<29; // Default so that size (2^lgsize) is 512MB
	} else if (size > (1<<MAX_KVAL-1)) {
		// If we've exceeded our memory size, then there's an error and we should report it and set our errno to ENOMEM
		mem_error(); 
		return errno;
	} else {
		size = next_best_two(size);
		mem_pool.start = mmap(NULL, pow(2,size), PROT_READ|PROT_WRITE, MAP_SHARED, ,); // Set our start point for our pool
		mem_pool.size = size;
	}
	// Get the lgsize of our desired size
	mem_pool.lgsize = log_two(mem_pool.size);

	//Set the initial block header
	mem_pool.avail[size].tag = 1; // Set to available
	mem_pool.avail[size].kval = mem_pool.lgsize;
	mem_pool.avail[size].next = NULL;
	mem_pool.avail[size].prev = NULL;
	
	return true;
}


void *buddy_malloc(size_t size)
{
	return NULL;
}

/**
 * This function clears out the necessary amount of memory
 * in the specified memory block, for the given size
 * 
 * @param nmemb - the nth memory block we want
 * @param size - the size of memory we want to clear
 */
void *buddy_calloc(size_t nmemb, size_t size) 
{
	size_t best_two;
	int i;

	best_two = next_best_two(nmemb * size);
	void *req = buddy_malloc(best_two);

	for (i = 0; i < best_two; i++)
	{
		req = '0'; // Clear out the memory for this block
		req++;
	}
	
	return req;
}

void *buddy_realloc(void *ptr, size_t size) 
{
	return NULL;
}

void buddy_free(void *ptr) 
{

}

/* Required method for unit testing */
void print_buddy_lists(void)
{
	
}

/* Required method for unit testing */
int get_min_k(void) {
	int i;
	int min_k = MAX_KVAL; // Set this to our max

	// Go through the list of available buddy blocks and see who's got the smallest kvalue
	for (i = 0; i < MAX_KVAL; i++)
	{
		min_k = min_k < pool.avail[i].kval ? pool.avail[i].kval : min_k;
	}
	
	return min_k;
}

/* Required method for unit testing */
int get_max_k(void) {
	return 0;
}

/**
 * This is a helper to return the lgsize of our 
 * desired memory size.
 * 
 * @param size - the size we requested
 */ 
int log_two(size_t size) {
	return log(size)/log(2);
}

/**
 * This is a helper for determining the next biggest 
 * integer that is a power of two based on the size
 * we have requested
 * 
 * @param size - the size we requested
 * @return the next biggest power of two int
 */
int next_best_two(size_t size) {
	if (size < 2) 
	{
		return 0;
	}

	int next = 1;

	while (next < size)
	{
		next <<= 1; // Shift our bit over by one each time until we get to the next biggest size that's a power of 2
	}
	
	return log_two(next);
}

/**
 * Helper function for printing out an error if we need
 * to let the user know that we've encountered ENOMEM
 */
void mem_error() {
	fprintf(stderr, "The program has encountered a memory error, it will now quit");
	errno = ENOMEM;
	exit(EXIT_FAILURE);
}


/*
 *
 *  Definition for malloc et al preload wedge
 *    These are wrappers for the buddy versions
 *    of the cooresponding methods implemented 
 *    above.  This will be completed in part 2.
 */
#ifdef BUDDY_PRELOAD
void * malloc(size_t size) 
{
	return NULL;
}

void *calloc(size_t nmemb, size_t size) 
{
	return NULL;
}

void *realloc(void *ptr, size_t size)
{
	return NULL;
} 

void free(void *ptr) 
{
	return NULL;
}

#endif /* BUDDY_PRELOAD */
