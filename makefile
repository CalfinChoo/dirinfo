ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

all: main.o
	$(CC) -o test main.o

main.o: main.c
	$(CC) -c main.c

run:
	./test

memcheck:
	valgrind --leak-check=yes ./test

clean:
	rm *.o
	rm *~
