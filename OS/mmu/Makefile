CC=g++
CFLAGS=-c -Wall
LFLAGS=
OBJS=main.o memory_manager.o bit_operations.o PR_algorithm_base.o RandomNumber.o FIFO.o Random.o SecondChance.o ClockFrame.o ClockVirtual.o

mmu-executable: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o mmu-executable

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

bit_operations.o: bit_operations.cpp bit_operations.h
	$(CC) $(CFLAGS) bit_operations.cpp
	
memory_manager.o: memory_manager.cpp memory_manager.h
	$(CC) $(CFLAGS) memory_manager.cpp

PR_algorithm_base.o: PR_algorithm_base.cpp PR_algorithm_base.h
	$(CC) $(CFLAGS) PR_algorithm_base.cpp

RandomNumber.o: RandomNumber.cpp RandomNumber.h
	$(CC) $(CFLAGS) RandomNumber.cpp

FIFO.o: FIFO.cpp FIFO.h
	$(CC) $(CFLAGS) FIFO.cpp

Random.o: Random.cpp Random.h
	$(CC) $(CFLAGS) Random.cpp

SecondChance.o: SecondChance.cpp SecondChance.h
	$(CC) $(CFLAGS) SecondChance.cpp

ClockFrame.o: ClockFrame.cpp ClockFrame.h
	$(CC) $(CFLAGS) ClockFrame.cpp

ClockVirtual.o: ClockVirtual.cpp ClockVirtual.h
	$(CC) $(CFLAGS) ClockVirtual.cpp

clean:
	rm -rf *.o

