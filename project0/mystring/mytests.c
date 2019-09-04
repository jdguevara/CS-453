#include "mystring.h"

int main(int argc, char**argv)
{
	//printf("fix me\n");

	/* Test out the mystrncpy function */
	char* dest;
	char* src = "Hello World!";


	//dest = mystrncpy(dest, src, 4);

	printf("The mystrncpy string is: %s\n", mystrncpy(dest, src, 4));

	return 0;
}
