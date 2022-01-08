#include <stdio.h>
#include <stdlib.h>
#include "nodes.h"

Edge *createEdge(int weight, Vertex *to);
Vertex *createVertex();
void deleteVertex();
LinkedList *createLinkedList();
void insertIntoList(LinkedList *list, Edge *edge);
void freeGraph();
char createUserList();
void freeEdge(Edge *current);
bool graphIsNull();
char addVertex();
void freeVertex(Vertex *current);
void printVertex(Vertex *vertex);
void printGraph();
int getWeight(int from, int to);

int numVertices;
Vertex **vertices;

#define DIVIDER 'n'
