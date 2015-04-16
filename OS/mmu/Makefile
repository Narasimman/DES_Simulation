CC=g++
CFLAGS=-c -Wall
LFLAGS=
OBJS=main.o memory_manager.o bit_operations.o PR_algorithm_base.o FIFO.o

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

FIFO.o: FIFO.cpp FIFO.h
	$(CC) $(CFLAGS) FIFO.cpp

clean:
	rm -rf *.o

