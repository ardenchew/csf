CC = cc

sim: sim.o error.o collect.o process.o dump.o
	$(CC) -o sim sim.o error.o collect.o process.o dump.o

dump.o: dump.c dump.h
	$(CC) -c dump.c

process.o: process.c process.h error.h
	$(CC) -c process.c

collect.o: collect.c collect.h
	$(CC) -c collect.c

error.o: error.c error.h
	$(CC) -c error.c

sim.o: sim.c error.h
	$(CC) -c sim.c

clean:
	rm -f *.o sim

