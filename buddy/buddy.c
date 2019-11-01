#include "buddy.h"

/* supports memory upto 2^(MAX_KVAL-1) (or 64 GB) in size */
#define  MAX_KVAL  37

/* the header for an available block */
struct block_header {
	short tag;
	short kval;
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

/*
 * Public Methods 
 */
int buddy_init(size_t size) 
{ 
	return FALSE;
}


void *buddy_malloc(size_t size)
{
	return NULL;
}

void *buddy_calloc(size_t nmemb, size_t size) 
{
	return NULL;
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
	return 0;
}

/* Required method for unit testing */
int get_max_k(void) {
	return 0;
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
