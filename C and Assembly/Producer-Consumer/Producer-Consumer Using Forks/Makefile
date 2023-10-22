# @(#) Makefile 1.2 95/04/27 Richard.Marejka@Canada.Sun.COM
#
# Makefile for part1 program.
#

CFLAGS	= -v -D_REENTRANT
LIBS	= -lpthread

all	: part2 producer consumer

clean	:
	rm -f part2 *.o  a.out core
	rm -f producer *.o a.out core
	rm -f consumer *.o a.out core

part2 : part2.c
	$(CC) $(CFLAGS) -o part2 part2.c part2.h $(LIBS)

producer : producer.c
	$(CC) $(CFLAGS) -o producer producer.c part2.h $(LIBS)

consumer : consumer.c
	$(CC) $(CFLAGS) -o consumer consumer.c part2.h $(LIBS)
