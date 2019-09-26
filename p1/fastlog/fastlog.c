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
int readIndex;
int writeIndex;

void fastlog_init(void)
{
    bufferPtr = malloc(sizeof(struct entry)*MAX_LOG_ENTRY);
    writeIndex = 0;
    readIndex = 0;
}


void fastlog_write(LEVEL lvl, char *text)
{
    // Check if we need to reset
    check_buff_end();
    time_t ltime;
    ltime = time(NULL);

    bufferPtr[writeIndex]->lvl = lvl;
    bufferPtr[writeIndex}->message = strcpy(text);
    bufferPtr[writeIndex}->pid = getpid();
    bufferPtr[writeIndex}->time = ltime;
    writeIndex++;
}

void check_buff_end() {
    if (writeIndex == MAX_LOG_ENTRY) {
        writeIndex = 0;
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
