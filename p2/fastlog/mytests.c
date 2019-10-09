#include "fastlog.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int main (void)

{
	// First test buffer
    fastlog_init();
    fastlog_write(ERROR, "1");
    fastlog_write(INFO, "2");
    fastlog_write(WARNING, "3");
    fastlog_write(WARNING, "4");
    fastlog_write(ERROR, "5");
    fastlog_write(ERROR, "6");
    fastlog_write(WARNING, "7");
    fastlog_write(ERROR, "8");
	kill(0, SIGINT);
    fastlog_write(ERROR, "9");
    fastlog_write(INFO, "");
    fastlog_write(WARNING, NULL);
    kill(0, SIGUSR1); // Use this to dump the file instead of fastlog_dump()

    fastlog_dump(); // Use this to formally dump the buffer, check to see that doing this will result in duplicate output
    kill(0, SIGINT);

	// Second test buffer
	fastlog_init();
    fastlog_write(WARNING, "THIS IS A WARNING");
    fastlog_write(INFO, "THIS IS INFO");
    fastlog_write(ERROR, "3");
    fastlog_write(WARNING, "ANOTHER WARNING");
    fastlog_write(ERROR, "5");
    fastlog_write(ERROR, "6");
    kill(0, SIGSEGV);
    //fastlog_dump();
    return 0;
}
