CC = g++

asm: asm.o process.o operate.o write.o error.o
	$(CC) -o asm asm.o process.o operate.o write.o error.o

error.o: error.cpp error.h
	$(CC) -c error.cpp

write.o: write.cpp write.h error.h
	$(CC) -c write.cpp

operate.o: operate.cpp operate.h error.h
	$(CC) -c operate.cpp

process.o: process.cpp process.h write.h operate.h error.h
	$(CC) -c process.cpp

asm.o: asm.cpp process.h error.h
	$(CC) -c asm.cpp

clean:
	rm -f *.o asm

