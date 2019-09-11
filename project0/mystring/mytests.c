#include "mystring.h"
#include <stdlib.h>

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

	printf("** Begin - Copy strings **\n\n");
	printf("String to copy using mystrncpy(): '%s'\n\n", src1);
	// Test Case #1: n-bytes is less than src length
	dest1 = mystrncpy(dest1, src1, 4);

	printf("Case 1: Bytes copied are less than string length\n");
	printf("\tBytes copied: 4\n");
	printf("\tResulting copy: '%s'\n\n", dest1);

	// Free memory after use
	free(dest1);

	// Test Case #2: n-bytes is longer than src length
	dest1 = mystrncpy(dest1, src1, 16);
	
	printf("Case 2: Bytes copied are more than string length\n");
	printf("\tBytes copied: 16\n");
	printf("\tResulting copy: '%s'", dest1);

    // Free memory
    free(dest1);

	/* Test out mystrncat function */
	char* dest2 = "Hello There! ";
	char* src2  = "General Kenobi";
	size_t n2 = 7;

	printf("\n\n** Strings will be concatenated now! ** \n");
	printf("\nDest string for mystrncat(): '%s'\n", dest2);
	printf("Src string for mystrncat(): '%s'\n\n", src2);

	// Test Case #1: n-bytes is less than src length
	dest2 = mystrncat(dest2, src2, n2);

	printf("Case 1: Bytes copied are less than src string length\n");
	printf("\tBytes copied: %ld\n", n2);
	printf("\tResulting concatenation: '%s'\n\n", dest2);

	// Free memory
	free(dest2);

    // Test Case #2: n-bytes greater than both strings
    n2 = 20;
    dest2 = "Hello There! ";
    dest2 = mystrncat(dest2, src2, n2);

    printf("Case 2: Bytes copied are greater than both string lengths\n");
    printf("\tBytes copied: %ld\n", n2);
    printf("\tResulting concatenation: '%s'\n\n", dest2);

    // Free memory
    free(dest2);

    // Test Case #3: empty dest

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

    // Test Case #2: Same string
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

    /* Test out the tokenizer */
    printf("** Strings will be tokenized now! **\n\n");
    // Test Case #1: "Same" string but with one character caps locked
    char* line = "Hello, How are you?";
    char* delimiter = ",";

    printf("\tLine: '%s'\n", line);
    printf("\tDelimiter: '%s'\n", delimiter);
    printf("\tResult: %d\n\n", mystrncmp(str1, str2, 5));


    return 0;
}
