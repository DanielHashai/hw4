all:
	gcc -Wall  -std=c99 -c main.c -c edges.c -c algo.c
	gcc -o graph main.o edges.o algo.o

clean:
	rm -rf *.o *.a *.so
