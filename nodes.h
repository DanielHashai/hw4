#ifndef NODES_H_
#define NODES_H_

#include "globals.h"

#define MAX_WEIGHT 9999999

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
	bool visited;
};

struct _LinkedList {
	Edge *head;
	Edge *tail;
	int size;
};

#endif
