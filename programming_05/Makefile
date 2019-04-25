CC = g++

branch: branch.o
	$(CC) -o branch branch.o

branch.o: branch.cpp branch.h
	$(CC) -c branch.cpp branch.h

clean:
	rm -f *.o branch

