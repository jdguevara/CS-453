#include "mystring.h"


char *mystrncpy(char *dest, const char *src, size_t n)
{
	size_t i;

	// Allocate enough size in dest to copy src into it
	dest = malloc(sizeof(char) * n); 
	
	// Check to see if src is shorter than the number of bytes
	if(strlen(src) < n) {
		strcpy(dest, src);
		for (i = strlen(src); i < n; i++)
		{
			dest[i] = '\0';
		}
		
	} else {
		for (i = 0; i < n; i++) {
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
