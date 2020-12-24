# Makefile for Battleship

CC = gcc
LD = gcc

# specify compile and link options
CFLAGS = -c -std=c99 -pedantic-errors -Wmissing-prototypes -Wall
LFLAGS = -Wall

OBJS = main.o Game.o
PROG = battleship

default: $(PROG)

$(PROG): $(OBJS)
	$(LD) $(LFLAGS) $(OBJS) -o $(PROG)

main.o: main.c Game.h
	$(CC) $(CFLAGS) main.c

Game.o: Game.c Game.h
	$(CC) $(CFLAGS) Game.c

clean:
	rm -f *.o

real_clean:
	rm -f *.o
	rm -f $(PROG)
