#include "fastlog.h"
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

struct entry {
    pid_t pid;
    struct timespec time;
    LEVEL lvl; 
    char message[MAX_MSG_LENGTH];
};

struct sigaction sigact;
// Personal function prototypes for compiler
void check_buff_end(void);
void sig_handler(int sig);

// Globals
struct entry buffer[MAX_LOG_ENTRY];
struct entry *bufferPtr;
int counter;

/**
 * This is the function that initializes our necessary items
 */
void fastlog_init(void)
{
	// Set up pointer to array (make sure we've got space for all entries)
	//bufferPtr = malloc(sizeof(struct entry) * MAX_LOG_ENTRY);
	bufferPtr = buffer;

	// Initialize our sigaction struct
	memset(&sigact, '\0', sizeof(sigact));

    // Use the sa_sigaction field because the handles has two additional parameters
    sigact.sa_handler = &sig_handler;

    // Set our handlers
    sigaction(SIGINT, &sigact, NULL);
    sigaction(SIGUSR1, &sigact, NULL);
    sigaction(SIGSEGV, &sigact, NULL);

    // Initialize counter to zero
	counter = 0;
}

/**
 * This is helps to write the necessary logs to our buffer
 * @param lvl - This refers to the enum cataloguing the message
 * @param text - This is the message associated with this entry
 */
void fastlog_write(LEVEL lvl, char *text)
{
    // Check overflow and exit if so
    if (counter < 0) {
        return;
    }

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
 * Write all valid logs to stderr using the following format:
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
	char bufferStr[1024]; // This is an arbitrary string length

    while (counter < MAX_LOG_ENTRY) {
		// Make sure our string is clear before every use
		memset(bufferStr, 0, sizeof(bufferStr));

        // Pass stored values into easier-to-handle vars
        bufferPid = (long) bufferPtr[counter].pid;
        bufferLevel = bufferPtr[counter].lvl;
        bufferMessage = bufferPtr[counter].message;

        // Time will need to be formatted to readable human standards
        my_tm = localtime(&bufferPtr[counter].time.tv_sec);
        strftime(bufferTime, MAX_MSG_LENGTH, "%F %I:%M:%S", my_tm);

		// Build up the line we want for the current element in the buffer
		snprintf(bufferStr, sizeof(bufferStr), "[%ld]-[%s.%.9ld]-[%d]-<%s>\n", bufferPid, bufferTime, bufferPtr[counter].time.tv_nsec, bufferLevel, bufferMessage);

		// Write out the string we built to stderr - 1024 bytes will be written since it would allocate enough space for our arbitrary buffer string length
		write(2, bufferStr, 1024);
        counter++;
        // nanosleep((const struct timespec[]){{0, 500000000L}}, NULL); // This was something I added for my own amusement
    }
    
	// Free up our bufferTime string
    free(bufferTime);
    bufferTime = NULL;
}

/**
 * This function will take whatever the signal is and act according to the project requirements.
 * @param sig - The signal that we'll be switching and acting on
 */
void sig_handler(int sig) {
    char sigsevstr[1024];

    switch (sig) {
        case SIGUSR1:
            // If SIGUSR1 is the signal we catch, then dump our buffer
            fastlog_dump();
            fflush(stdout);
            break;
        case SIGINT:
            // If SIGINT is what we catch, then write that CTRL-C was caught, ignored, and carry on
            fastlog_write(ERROR, "CTRL-C ignored");
            break;
        case SIGSEGV:
            // If SIGSEGV is hit, then we want to let the user know the system has crashed and we want to dump the buffer

            // Make sure our string is clear before every use
            memset(sigsevstr, 0, sizeof(sigsevstr));

            // Build up the line we want
            snprintf(sigsevstr, sizeof(sigsevstr), "\nSegmentation fault encountered...dumping buffer.\n");
            write(2, sigsevstr, 1024);
           // sleep(1); // Unnecessary but I want some flair for this action

            // Dump buffer
            fastlog_dump();

            // Exit
            exit(-1);
            break;
    }

}
