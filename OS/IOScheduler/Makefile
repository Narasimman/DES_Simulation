CC=g++
CFLAGS=-c -Wall
LFLAGS=
OBJS=main.o event.o processor.o scheduler.o FIFO.o SSTF.o SCAN.o CSCAN.o FSCAN.o

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
	
SSTF.o: SSTF.cpp SSTF.h
	$(CC) $(CFLAGS) SSTF.cpp

SCAN.o: SCAN.cpp SCAN.h
	$(CC) $(CFLAGS) SCAN.cpp

CSCAN.o: CSCAN.cpp CSCAN.h
	$(CC) $(CFLAGS) CSCAN.cpp

FSCAN.o: FSCAN.cpp FSCAN.h
	$(CC) $(CFLAGS) FSCAN.cpp

clean:
	rm -rf *.o
