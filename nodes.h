#ifndef NODES_H_
#define NODES_H_

#define MAX_WEIGHT 9999999
#define null NULL

typedef enum {false, true} bool;
typedef struct _Edge Edge;
typedef struct _Vertex Vertex;
typedef struct _LinkedList LinkedList;

struct _Edge {
	int weight;
	Vertex *to;
	Edge *next;
};

struct _Vertex {
	int value;
	LinkedList *edges;
	int smallestWeight;
};

struct _LinkedList {
	Edge *head;
	Edge *tail;
	int size;
};

# define DEBUG() printf("%s %d", __FILE__, __LINE__);

#endif
