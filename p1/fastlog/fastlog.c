#include "fastlog.h"
#include <unistd.h>
#include <time.h>

struct entry {
    pid_t pid;
    struct timespec time;
    LEVEL lvl; 
    char message[MAX_MSG_LENGTH];
};

struct entry *bufferPtr;
int counter = 0;

void fastlog_init(void)
{
	// Set up a buffer array of entries of MAX_LOG_ENTRY size
	struct entry buffer[MAX_LOG_ENTRY];
	bufferPtr = buffer;
}


void fastlog_write(LEVEL lvl, char *text)
{
    // Check if we need to reset
    check_buff_end();
    time_t ltime;
    ltime = time(NULL);

    buffer[counter]->lvl = lvl;
    buffer[counter]->message = strcpy(text);
    buffer[counter]->pid = getpid();
    buffer[counter]->time = ltime;
    counter++;
}

void check_buff_end() {
    if (counter == 500) {
        counter = 0;
    }
}

/**
 * Print all valid logs to stderr using the following format:
 * [pid]-[timestamp]-[LEVEL]-<message_text>"
 *
 * NOTE: Logs should be printed from oldest to newest
 */
void fastlog_dump(void) 
{
    int counter = 0;
    while (bufferPtr) {
        printf("[%ld]-[%s]-[%d]-<%s>", *(bufferPtr + counter)->pid, asctime(*(bufferPtr + counter)->time), *(bufferPtr + counter)->lvl, *(bufferPtr + counter)->message);
        counter++;
    }
}
