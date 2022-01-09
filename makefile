all: graph

graph: globals.o edges.o algo.o main.o
	gcc $^ -o $@

%.o: %.c globals.h nodes.h edges.h algo.h
	gcc -std=c99 -c $< -o $@

clean:
	rm -rf *.o *.a *.so
