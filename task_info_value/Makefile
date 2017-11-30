# The LLVM-OpenMP shared library should be contained in the INSTALL_PREFIX folder
# otherwise just properly set the LD_LIBRARY_PATH variable
INSTALL_PREFIX?=${LOCAL_ENV}
CC=gcc
CFLAGS=-Wall -D_GNU_SOURCE -O3 -std=c99 -fopenmp

default: main 

main: 
	${CC} ${CFLAGS} -L${INSTALL_PREFIX}/lib -o test.x test.c

clean:
	rm -f *.o *.so 
