CC=g++
CFLAGS=-c -Wall
LFLAGS=
OBJS=main.o event.o processor.o scheduler.o FIFO.o

iosched: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o iosched

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

event.o: event.cpp event.h
	$(CC) $(CFLAGS) event.cpp

processor.o: processor.cpp processor.h
	$(CC) $(CFLAGS) processor.cpp

scheduler.o: scheduler.cpp scheduler.h
	$(CC) $(CFLAGS) scheduler.cpp

FIFO.o: FIFO.cpp FIFO.h
	$(CC) $(CFLAGS) FIFO.cpp

clean:
	rm -rf *.o
