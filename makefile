all:
	gcc -Wall  -std=c99 -c main.c -c edges.c -c algo.c -c globals.c
	gcc -o graph main.o edges.o algo.o globals.o

clean:
	rm -rf *.o *.a *.so
