CC=g++
CFLAGS=-c -Wall
LFLAGS=
OBJS=main.o 

iosched: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o iosched

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

clean:
	rm -rf *.o

