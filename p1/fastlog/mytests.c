#include "fastlog.h"
#include <stdlib.h>
#include <stdio.h>

int main (void)

{
    fastlog_init();
    fastlog_write(ERROR, "1");
    fastlog_write(INFO, "2");
    fastlog_write(WARNING, "3");
    fastlog_write(WARNING, "4");
    fastlog_write(ERROR, "5");
    fastlog_write(ERROR, "6");
    fastlog_write(WARNING, "7");
    fastlog_write(ERROR, "8");
    fastlog_write(ERROR, "9");
    fastlog_write(INFO, "");
    fastlog_write(WARNING, NULL);
    fastlog_dump();

	fastlog_init();
    fastlog_write(WARNING, "THIS IS A WARNING");
    fastlog_write(INFO, "THIS IS INFO");
    fastlog_write(ERROR, "3");
    fastlog_write(WARNING, "ANOTHER WARNING");
    fastlog_write(ERROR, "5");
    fastlog_write(ERROR, "6");
    fastlog_dump();
    return 0;
}
