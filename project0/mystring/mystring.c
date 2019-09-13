#include <stdlib.h>
#include <string.h>
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
    // Return if either dest or src are NULL
    if(!dest || !src) {
        return NULL;
    }

    char * ptr = dest;
    size_t src_len = strlen(src);
	size_t i;
	
	// Loop for as many bytes as indicated
	for (i = 0; i < n; i++)
		{
	        // If we go past the original src length continue adding null characters
            if(i > src_len) {
                *ptr++ = '\0';
            // Otherwise, just copy the next byte from src
            } else {
                *ptr++ = *src++;
            }
		}

	return dest;
}

/*
	Implementation of mystrncat(), where the function
	should concatenate n-bytes of src to dest, and should
	always be null-terminated. If the src string length is
	greater than n-bytes then dest should only have n-bytes
	+ a null character added to it. Otherwise, all of src
	and the null character.

	params: char * dest - Our destination pointer
		    char * src - Our source string/pointer
			size_t n - The determined number of bytes to concat
						to dest from src
	
	return: properly string containing concatenated n-bytes
 */
char *mystrncat(char *dest, const char *src, size_t n)
{
    // Return if either dest or src are NULL
    if(!dest || !src) {
        return NULL;
    }

    size_t dest_len = strlen(dest);
    char * ptr = dest + dest_len;
    int i;

    // Add n-bytes from source until the null character is found
    for (i = 0 ; i < n && *src != '\0'; i++) {
        *ptr++ = *src++;
    }

    // Cap the string with null character
    *ptr = '\0';

    return dest;
}

/*
 * Implementation of the mystrncmp() function in mystring.h
 * It should take in two strings, compare the first n characters
 * of each string and determine whether the first string is
 * greater than, less than, or equal to the second string.
 *
 * Params: const char * s1
 *         const char * s2
 *
 * Return: -1 if s1 < s2
 *          0 if s1 = s2
 *          1 if s1 > s2
 */
int mystrncmp(const char *s1, const char *s2, size_t n)
{
    size_t i;
    int val;

    val = 0;
    for (i = 0; i < n || s1[i] != '\0' || s2[i] != '\0'; ++i) {
        val += *s1++ - *s2++;
    }

    if (val == 0) {
        return 0;
    } else if (val > 0) {
        return 1;
    } else {
        return -1;
    }
}

/*
 * Implementation of the tokenizer() function from mystring.h
 * Parse a given string into tokens using provide delimiters. This function
 * returns a token_data struct that contains the array of tokens and the count
 * of tokens found.
 *
 * Params: const char * line - line/string to tokenize
 *         char * delimiter - series of characters that determines how string is split
 *
 * Return: token_data struct containing the array of tokens found using the delimiter
 *		   and a count for how many tokens were found
 */
struct token_data *tokenizer(const char *line, char *delimiter)
{
    // Return if either the line or delimiter are NULL
    if(!line || !delimiter) {
        return NULL;
    }

    char* editLine = strdup(line);
    struct token_data tokens;
	struct token_data *tokenizerP = malloc(sizeof(struct token_data));
	int i;

	// Point to wherever our tokenizer struct is located
    tokenizerP = &tokens;

    // Allocate enough space for tokens
    tokenizerP->tokens = malloc(sizeof(char*) * MAX_TOKENS);

	tokenizerP->num_tokens = 0;

    // Get the first token from our line
    tokenizerP->tokens[0] = strtok(editLine, delimiter);
    tokenizerP->num_tokens++;
	
	i = 0;
	//Until the end of the line
    while(tokenizerP->tokens[i] != NULL) {
		i++;
		tokenizerP->tokens[i] = strtok(NULL, delimiter);
		tokenizerP->num_tokens++;
	}

	return tokenizerP;
}

/*
 * Method for freeing up the pointers found in our token_data struct
 *
 * Params: token_data * tokes - pointer to data struct
 */
void free_tok(struct token_data *tokes)
{
}
