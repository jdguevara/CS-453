#include "mystring.h"

int main(int argc, char**argv)
{
	//printf("fix me\n");

	/* Test out the mystrncpy function */
	char* dest1;
	char* src = "Hello World!";

	printf("The mystrncpy string is: %s\n", mystrncpy(dest1, src, 4));

	// Free memory used
	free(dest1);

	return 0;
}
