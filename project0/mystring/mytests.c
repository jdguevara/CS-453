#include "mystring.h"

int main(int argc, char**argv)
{
	//printf("fix me\n");

	/* Test out the mystrncpy function */
	char* dest1;
	char* src = "Hello World!";

	dest1 = mystrncpy(dest1, src, 4);

	printf("The mystrncpy string is: %s\n", dest1);

	// Free memory
	free(dest1);
	return 0;
}
