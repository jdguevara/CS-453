#ifndef MYSTRING_H_
#define MYSTRING__H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

/*
 * This function copies at most n bytes of src, including the terminating null byte ('\0'),
 * to the buffer pointed to by dest.  The strings may not overlap, and the destination string
 * dest must be large enough to receive the copy.
 *
 * Warning: If there is no null byte among the first n bytes of src, the string placed in
 * dest will not be null-terminated.
 *
 * If the length of src is less than n, this function writes additional null bytes to dest
 * to ensure that a total of n bytes are written.
 * 
 * The strncpy() function returns a pointer to the destination string dest.
*/
char *mystrncpy(char *dest, const char *src, size_t n);

/*
 * This function appends the src string to the dest string. It will use at most n bytes from src.
 * The resulting string in dest is always null-terminated.  The strings may not overlap, and the
 * dest string must have enough space for the result.
 *
 * Note:  src does not need to be null-terminated if it contains n or more bytes.
 *
 * If src contains n or more bytes, this function writes n+1 bytes to dest (n from src plus the
 * terminating null byte).  Therefore, the size of dest must be at least strlen(dest)+n+1.
 * 
 *  * The strncat() function returns a pointer to the destination string dest.
 */
char *mystrncat(char *dest, const char *src, size_t n);

/*
 * This function compares only the first (at most) n bytes of s1 and s2.
 * It returns an integer less than, equal to, or greater than zero if s1 is
 * found, respectively, to be less than, to match, or be greater than s2.
*/
int mystrncmp(const char *s1, const char *s2, size_t n);


#define MAX_TOKENS 2048

struct token_data {
    char **tokens;
    int num_tokens;
};

 /*
  * Parse a given string into tokens using provide delimiters. This function
  * returns a token_data struct that contains the array of tokens and the count 
  * of tokens found.
  *
  * NOTE: This function calls malloc internally. The caller must call free_tok
  * to free memory.
  * 
  * Returns NULL if line or delimiter is NULL or if an error occurs during 
  *    tokenization.
 */
 struct token_data *tokenizer(const char *line, char *delimiter);


/*
 * Frees the memory that was allocated with tokenizer.
*/
void free_tok(struct token_data *tokes);


#ifdef __cplusplus
}
#endif

#endif //MYSTRING_H_
