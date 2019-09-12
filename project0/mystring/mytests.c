#include "mystring.h"
#include <stdlib.h>
#include <string.h>

/*
 * Tests written for my implementations of the string modifier functions
 *
 * @author: Jaime Guevara
 */
int main(int argc, char**argv)
{
	/* Test out the mystrncpy function */
	char* dest1; 
	char* src1 = "Hello World!";
	size_t n = 4;

    printf("** Begin - Copy strings **\n\n");
	printf("String to copy using mystrncpy(): '%s'\n\n", src1);

	// Test Case #1: n-bytes is less than src length
    dest1 = malloc(sizeof(char) * n);
	dest1 = mystrncpy(dest1, src1, n);

	printf("Case 1: Bytes copied are less than string length\n");
	printf("\tBytes copied: %ld\n", n);
	printf("\tResulting copy: '%s'\n\n", dest1);

	// Free memory after use
	free(dest1);

	// Test Case #2: n-bytes is longer than src length
    n = 16;
    dest1 = malloc(sizeof(char) * n);
	dest1 = mystrncpy(dest1, src1, n);
	
	printf("Case 2: Bytes copied are more than string length\n");
	printf("\tBytes copied: %ld\n", n);
	printf("\tResulting copy: '%s'\n\n", dest1);

    // Free memory
    free(dest1);

    // Test Case #3: one string is null
    n = 16;
    dest1 = malloc(sizeof(char) * n);
    dest1 = mystrncpy(dest1, NULL, n);

    printf("Case 3: One string is null\n");
    printf("\tBytes copied: %ld\n", n);
    printf("\tResulting copy: '%s'\n\n", dest1);

    // Free memory
    free(dest1);

    /* Test out string concatenation */
    printf("** Concatenation Tests **\n\n");

    // Case 1: destination string is not empty
    char* original_dest = "Hello "; // Not too sure about this, but it'll serve with gauging malloc
    char* dest;
    const char* src = "World!";
    n = 6;
    int dest_size = strlen(original_dest);

    // Allocate enough memory to hold dest, n-bytes from src, and null
    dest = (char*) malloc(dest_size + (sizeof(char) * n) + 1);

    // Using the copy function to pass a char* to dest, assigning a string breaks the malloc and further testing
    // of the implementation of mystrncpy()
    mystrncpy(dest, original_dest, n);

    printf("Case 1: destination string is not empty\n");
    printf("\tDestination string: '%s'\n", dest);
    printf("\tConcat source string: '%s'\n", src);
    printf("\tBytes to concatenate: %ld\n", n);

    // Get our concatenated string
    dest = strncat(dest, src, n);

    printf("\n\tResulting concat: '%s'\n\n", dest);

    // Free memory
    free(dest);

    // Case 2: destination isn't empty and concatenating less bytes than the length of source
    n = 4;
    dest = (char*) malloc(dest_size + (sizeof(char) * n) + 1);
    strcpy(dest, original_dest);

    printf("Case 2: destination isn't empty and concatenating less bytes than the length of source\n");
    printf("\tDestination string: '%s'\n", dest);
    printf("\tConcat source string: '%s'\n", src);
    printf("\tBytes to concatenate: %ld\n", n);

    // Get our concatenated string
    dest = strncat(dest, src, n);

    printf("\n\tResulting concat: '%s'\n\n", dest);

    // Free memory
    free(dest);

    // Case 3: destination isn't empty and concatenating more bytes than the length of source
    n = 10;
    dest = (char*) malloc(dest_size + (sizeof(char) * n) + 1);
    strcpy(dest, original_dest);

    printf("Case 3: destination isn't empty and concatenating more bytes than the length of source\n");
    printf("\tDestination string: '%s'\n", dest);
    printf("\tConcat source string: '%s'\n", src);
    printf("\tBytes to concatenate: %ld\n", n);

    // Get our concatenated string
    dest = strncat(dest, src, n);

    printf("\n\tResulting concat: '%s'\n\n", dest);

    // Free memory
    free(dest);

    // Case 4: destination is empty
    n = 3; // Change this up just to make things different
    dest = (char*) malloc((sizeof(char) * n) + 1);

    printf("Case 3: destination isn't empty and concatenating more bytes than the length of source\n");
    printf("\tDestination string: '%s'\n", dest);
    printf("\tConcat source string: '%s'\n", src);
    printf("\tBytes to concatenate: %ld\n", n);

    // Get our concatenated string
    dest = strncat(dest, src, n);

    printf("\n\tResulting concat: '%s'\n\n", dest);

    // Free memory
    free(dest);

    /* Testing out mystrncmp() */
    printf("** Strings will be compared now! **\n"
           "Number of bytes used throughout: 5\n\n");
    // Test Case #1: "Same" string but with one character caps locked
	char* str1 = "hello";
    char* str2 = "Hello";

    printf("Case #1: Same word, one character is caps locked\n");
    printf("\tString 1: '%s'\n", str1);
    printf("\tString 2: '%s'\n", str2);
    printf("\tResult: %d\n\n", mystrncmp(str1, str2, 5));

    /* Test Case #2: Same string */
    str1 = "Hello";

    printf("Case #2: Same word\n");
    printf("\tString 1: '%s'\n", str1);
    printf("\tString 2: '%s'\n", str2);
    printf("\tResult: %d\n\n", mystrncmp(str1, str2, 5));

    // Test Case #3: Same as first test case in this series, but string order is swapped
    str1 = "hello";

    printf("Case #3: Same as Case #1 in this series, but string order is swapped when passed to function\n");
    printf("\tString 1: '%s'\n", str1);
    printf("\tString 2: '%s'\n", str2);
    printf("\tResult: %d\n\n", mystrncmp(str2, str1, 5));

    // Test Case #4: One string shorter than the other and number of bytes longer than s1
    str1 = "He";
    str2 = "Hello to you?";

    printf("Case #4: One string shorter than the other, and number of bytes longer than s1\n");
    printf("\tString 1: '%s'\n", str1);
    printf("\tString 2: '%s'\n", str2);
    printf("\tResult: %d\n", mystrncmp(str1, str2, 5));

    /* Test out the tokenizer*/
    printf("** Strings will be tokenized now! **\n\n");
    // Test Case #1: "Same" string but with one character caps locked
    char* line = "Hello, How are you?";
    char* delimiter = ",";

    struct token_data *tokens = tokenizer(line, delimiter);

    printf("\tLine: '%s'\n", line);
    printf("\tDelimiter: '%s'\n", delimiter);
    printf("\tFirst token: %d\n", tokens->num_tokens);


    return 0;
}
