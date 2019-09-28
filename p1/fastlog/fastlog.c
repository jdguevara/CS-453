#include "fastlog.h"
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct entry {
    pid_t pid;
    struct timespec time;
    LEVEL lvl; 
    char message[MAX_MSG_LENGTH];
};

void check_buff_end(void);

struct entry buffer[MAX_LOG_ENTRY];
struct entry *bufferPtr;
int counter;

void fastlog_init(void)
{
	// Set up pointer to array
	bufferPtr = malloc(sizeof(struct entry) * MAX_LOG_ENTRY);
	bufferPtr = buffer;
	counter = 0;
}


void fastlog_write(LEVEL lvl, char *text)
{
    // Check if we need to reset
    check_buff_end();

    bufferPtr[counter].lvl = lvl;
    strcpy(bufferPtr[counter].message, text);
    bufferPtr[counter].pid = getpid();
	clock_gettime(CLOCK_REALTIME, &bufferPtr[counter].time);
    counter++;
}

void check_buff_end() {
    if (counter == MAX_LOG_ENTRY) {
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

    while (counter < MAX_LOG_ENTRY) {
        long bufferPid = (long) bufferPtr[counter].pid;
        struct tm *my_tm = localtime(&bufferPtr[counter].time.tv_sec);
        int bufferLevel = bufferPtr[counter].lvl;
        char* bufferMessage = bufferPtr[counter].message;
        printf("[%ld]-[%s.%.9ld]-[%d]-<%s>\n", bufferPid, asctime(my_tm), bufferPtr[counter].time.tv_nsec, bufferLevel, bufferMessage);
        counter++;
    }
}
