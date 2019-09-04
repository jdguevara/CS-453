#include "mystring.h"

/*
	Implementation of mystrncpy(), where the functions 
	should copy the number of bytes, n, from src into dest

	params: char * dest - Our destination pointer
	        char * src - The source string
			size_t n - The number of bytes that should be copied
					   from src to dest
	
	return: properly allocated dest with the correct number of bytes
*/
char *mystrncpy(char *dest, const char *src, size_t n)
{
	size_t i;

	// Allocate enough size in dest to copy src into it
	dest = malloc(sizeof(char) * n); 
	
	// Loop for as many bytes as indicated
	for (i = 0; i < n; i++)
		{
			// check if we've gone past src length
			if (i > strlen(src)) {
				// fill remainder of dest with null character
				dest[i] = '\0';
			} else {
				// copy the correct byte from src to dest
				dest[i] = src[i];
			}
		}
	
	return dest;
}

char *mystrncat(char *dest, const char *src, size_t n)
{	
	return NULL;
}

int mystrncmp(const char *s1, const char *s2, size_t n)
{
	return -1;
}

struct token_data *tokenizer(const char *line, char *delimiter)
{
	return NULL;
}

void free_tok(struct token_data *tokes)
{
}
