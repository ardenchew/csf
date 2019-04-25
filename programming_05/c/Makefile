CC = cc

branch: branch.o
	$(CC) -o branch branch.o

branch.o: branch.c branch.h
	$(CC) -c branch.c branch.h

clean:
	rm -f *.o branch

