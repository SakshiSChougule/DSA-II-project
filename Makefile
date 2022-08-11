#makefile

all:#target
	gcc file.c freq.c tree.c pqueue.c stack.c code.c compress.c decompress.c main.c -o a.out
	
clear:
	rm*.o
