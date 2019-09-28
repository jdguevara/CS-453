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
void free_buff(void);

// Globals
struct entry buffer[MAX_LOG_ENTRY];
struct entry *bufferPtr;
int counter;

void fastlog_init(void)
{
	// Set up pointer to array (make sure we've got space for all entries)
	bufferPtr = malloc(sizeof(struct entry) * MAX_LOG_ENTRY);
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
    strcpy(bufferPtr[counter].message, text); // Message string (remember to copy, not just assign)
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

    while (counter < MAX_LOG_ENTRY) {
        // Check that our current entry isn't empty otherwise, increase counter and skip
        /*if(bufferPtr[counter] == NULL) {
            counter++;
            continue;
        }*/

        // Pass stored values into easier-to-handle vars
        long bufferPid = (long) bufferPtr[counter].pid;
        int bufferLevel = bufferPtr[counter].lvl;
        char* bufferMessage = bufferPtr[counter].message;

        // Time will need to be formatted to readable human standards
        struct tm *my_tm = localtime(&bufferPtr[counter].time.tv_sec);
        char* bufferTime = malloc(sizeof(char) * MAX_MSG_LENGTH);;
        strftime(bufferTime, MAX_MSG_LENGTH, "%F %I:%M:%S", my_tm);

        // Print out our logs //TODO: Make sure to print out based on timestamp age
		fprintf(stderr, "[%ld]-[%s.%.9ld]-[%d]-<%s>\n", bufferPid, bufferTime, bufferPtr[counter].time.tv_nsec, bufferLevel, bufferMessage);

        counter++;
    }

    // Free our buffer once we're done with our dump
    free_buff();
}

/**
 * Function to free up the buffer once it's contents are dumped
 */
 void free_buff() {
     free(bufferPtr[0].pid);
     free(bufferPtr);
 }
