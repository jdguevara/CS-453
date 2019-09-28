#include "fastlog.h"


int main (void)

{
    fastlog_init();
    fastlog_write(ERROR, "1");
    fastlog_write(ERROR, "2");
    fastlog_write(ERROR, "3");
    fastlog_write(ERROR, "4");
    fastlog_write(ERROR, "5");
    fastlog_write(ERROR, "6");
    fastlog_write(ERROR, "7");
    fastlog_write(ERROR, "8");
    fastlog_write(ERROR, "9");
    fastlog_write(ERROR, "10");
    fastlog_dump();

	fastlog_init();
    fastlog_write(ERROR, "1");
    fastlog_write(ERROR, "2");
    fastlog_write(ERROR, "3");
    fastlog_write(ERROR, "4");
    fastlog_write(ERROR, "5");
    fastlog_write(ERROR, "6");
    fastlog_dump();
    return 0;
}
