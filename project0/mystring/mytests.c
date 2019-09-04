#include "mystring.h"

int main(int argc, char**argv)
{
	//printf("fix me\n");

	/* Test out the mystrncpy function */
	char* dest1; 
	char* src1 = "Hello World!";

	printf("String to copy using mystrncpy(): '%s'\n\n", src1);
	// Test Case #1: n-bytes is less than src length
	dest1 = mystrncpy(dest1, src1, 4);

	printf("Case 1: Bytes copied are less than string length\n");
	printf("\tBytes copied: 4\n");
	printf("\tResulting copy: '%s'\n\n", dest1);

	// Test Case #2: n-bytes is longer than src length
	dest1 = mystrncpy(dest1, src1, 16);
	
	printf("Case 2: Bytes copied are more than string length\n");
	printf("\tBytes copied: 16\n");
	printf("\tResulting copy: '%s'", dest1);

	// Free memory
	free(dest1);
	return 0;
}
