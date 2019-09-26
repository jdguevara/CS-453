#include "fastlog.h"
#include <unistd.h>
#include <time.h>

struct entry {
    pid_t pid;
    struct timespec time;
    LEVEL lvl; 
    char message[MAX_MSG_LENGTH];
};



void fastlog_init(void)
{
	// Set up a buffer array of entries of MAX_LOG_ENTRY size
	struct entry buffer[MAX_LOG_ENTRY]; 
}


void fastlog_write(LEVEL lvl, char *text)
{
    /*need to implement this.
        
    HINT: 
    Don't forget that you should be copying stuff!!!
    String assignments in C don't work the same as in 
    java.
    
     */
}

void fastlog_dump(void) 
{

}
