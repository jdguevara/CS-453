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
	
	return: properly allocated string with the correct number of
		    bytes concatenated from src.
 */
char *mystrncat(char *dest, const char *src, size_t n)
{
    char* newDest; // Need somewhere to hold dest byte-for-byte
    size_t dest_len = strlen(dest);
    size_t i;

    newDest = malloc(dest_len + (sizeof(char)*n) + 1);

    // Copy over the stuff in dest (without this, the string in dest is overridden)
    for (i = 0; i < dest_len; i++) {
        newDest[i] = dest[i];
    }

    // Add n-bytes from source until the null character is found
    for (i = 0 ; i < n && src[i] != '\0' ; i++)
        newDest[dest_len + i] = src[i];

    // Cap the string with null character
    newDest[dest_len + i] = '\0';

    return newDest;
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
        val += s1[i] - s2[i];
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
 * Implementation of the tokenizer( ) function from mystring.h
 * Parse a given string into tokens using provide delimiters. This function
 * returns a token_data struct that contains the array of tokens and the count
 * of tokens found.
 *
 * Params: const char * line - line/string to tokenize
 *         char * delimiter - series of characters that determines how string is split
 *
 * Return:
 */
struct token_data *tokenizer(const char *line, char *delimiter)
{
    int i;
    int lineLength = strlen(line);
    int delimLenth = strlen(delimiter);
    static token_data * tokens = malloc(sizeof(token_data));

    tokens.num_tokens = 0;
    for (i = 0; i < lineLength; ++i) {
        for (int j = 0; j < delimLenth; ++j) {
            if (line[i] === delimiter[j]) {
                j++;
            } else {
                tokens.num_tokens++;
                continue;
            }
        }
    }
	return tokens;
}

void free_tok(struct token_data *tokes)
{
}
