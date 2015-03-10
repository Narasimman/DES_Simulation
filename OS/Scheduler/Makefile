CC=g++
CFLAGS=-c -Wall
LFLAGS=
OBJS=main.o process.o processor.o scheduler.o event.o FCFS.o LCFS.o SJF.o RR.o PRIO.o

sched: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o sched

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

process.o: process.cpp process.h
	$(CC) $(CFLAGS) process.cpp

processor.o: processor.cpp processor.h
	$(CC) $(CFLAGS) processor.cpp

FCFS.o: FCFS.cpp FCFS.h
	$(CC) $(CFLAGS) FCFS.cpp

LCFS.o: LCFS.cpp LCFS.h
	$(CC) $(CFLAGS) LCFS.cpp

SJF.o: SJF.cpp SJF.h
	$(CC) $(CFLAGS) SJF.cpp

RR.o: RR.cpp RR.h
	$(CC) $(CFLAGS) RR.cpp

PRIO.o: PRIO.cpp PRIO.h
	$(CC) $(CFLAGS) PRIO.cpp

scheduler.o: scheduler.cpp scheduler.h
	$(CC) $(CFLAGS) scheduler.cpp

event.o: event.cpp event.h
	$(CC) $(CFLAGS) event.cpp

clean:
	rm -rf *.o

