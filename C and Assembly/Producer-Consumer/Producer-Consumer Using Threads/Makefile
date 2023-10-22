# @(#) Makefile 1.2 95/04/27 Richard.Marejka@Canada.Sun.COM
#
# Makefile for part1 program.
#

CFLAGS	= -v -D_REENTRANT
LIBS	= -lpthread

all	: part1

clean	:
	rm -f part1 *.o  a.out core

part1 : part1.c
	$(CC) $(CFLAGS) -o part1 part1.c $(LIBS)  
