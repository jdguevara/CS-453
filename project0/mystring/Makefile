CC = gcc
CFLAGS = -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=gnu89 -O2 -fPIC -L.
LDFLAGS = -shared

all: libmystring mytests

mytests: mytests.o mystring.o
	$(CC) $(CFLAGS) $^ -o $@ 

libmystring: mystring.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@.so

# Note: For this test to run, the current directory
#   must be added to the LD_LIBRARY_PATH
#
#   export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:.
#
mylibtests: mytests.o
	$(CC) $(CFLAGS) $^ -o $@ -lmystring

clean:
	rm -f *.o *.d a.out mytests mylibtests libmystring.so
