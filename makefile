
CFLAGS=-g -std=c99 -Wall -I acutest/include

all: test
	./test

valgrind: test
	valgrind test --no-exec

getline.o: getline.c getline.h

tests.o: tests.c getline.h

test: getline.o tests.o
	cc -o test $^

clean:
	rm getline.o tests.o test
