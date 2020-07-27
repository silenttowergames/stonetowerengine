CC=gcc
CFLAGS=-Wall -g -pedantic -IC:\C\flecs-master\include

all: main

main: %.o
	$(CC) $(CFLAGS) -o bin/win64/main.exe $^

%.o: src/%.c
	$(CC) $(CCFLAFGS) -c $^
