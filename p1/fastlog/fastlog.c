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

// Personal function prototypes for compiler
void check_buff_end(void);

// Globals
struct entry buffer[MAX_LOG_ENTRY];
struct entry *bufferPtr;
int counter;

void fastlog_init(void)
{
	// Set up pointer to array (make sure we've got space for all entries)
	//bufferPtr = malloc(sizeof(struct entry) * MAX_LOG_ENTRY);
	bufferPtr = buffer;

	// Initialize counter to zero
	counter = 0;
}


void fastlog_write(LEVEL lvl, char *text)
{
    // Check if we need to reset our count
    check_buff_end();

    // Get the values we need for our entry
    bufferPtr[counter].lvl = lvl; // Level

	// Check for NULL strings
    if (text != NULL) {
        // Check length of string
        if(strlen(text) > MAX_MSG_LENGTH) {
            int strDiff = strlen(text) - MAX_MSG_LENGTH;
            strncpy(bufferPtr[counter].message, text, strlen(text) - strDiff);
        } else {
            strcpy(bufferPtr[counter].message, text); // Message string (remember to copy, not just assign)
        }
    } else {
		strcpy(bufferPtr[counter].message, "");
	}
    bufferPtr[counter].pid = getpid(); // Get the Process ID (PID)
	clock_gettime(CLOCK_REALTIME, &bufferPtr[counter].time); // Get the current time into our timespec

    counter++;
}

/**
 * This function serves to reset the counter once we reach our MAX_LOG_ENTRY size
 */
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
    // This counter is local, independent of our global
    int counter = 0;

    // More local vars
    long bufferPid;
    int bufferLevel;
    char* bufferMessage;
    struct tm *my_tm;
    char* bufferTime = malloc(sizeof(char) * MAX_MSG_LENGTH);

    while (counter < MAX_LOG_ENTRY) {
        // Pass stored values into easier-to-handle vars
        bufferPid = (long) bufferPtr[counter].pid;
        bufferLevel = bufferPtr[counter].lvl;
        bufferMessage = bufferPtr[counter].message;

        // Time will need to be formatted to readable human standards
        my_tm = localtime(&bufferPtr[counter].time.tv_sec);
        strftime(bufferTime, MAX_MSG_LENGTH, "%F %I:%M:%S", my_tm);

        // Print out our logs //TODO: Make sure to print out based on timestamp age (going to need to do this in part 2)
		fprintf(stderr, "[%ld]-[%s.%.9ld]-[%d]-<%s>\n", bufferPid, bufferTime, bufferPtr[counter].time.tv_nsec, bufferLevel, bufferMessage);

        counter++;
    }
    
	// Free up our bufferTime string
    free(bufferTime);
    bufferTime = NULL;
}
